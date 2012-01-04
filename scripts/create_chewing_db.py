#!/usr/bin/env python
# -*- coding: utf-8 -*-
from pydict import *
from id import *
from valid_hanzi import *
import sys
import bopomofo

def get_sheng_yun(pinyin):
    if pinyin == None:
        return None, None
    if pinyin == "ng":
        return "", "en"
    for i in xrange(2, 0, -1):
        t = pinyin[:i]
        if t in SHENGMU_DICT:
            return t, pinyin[len(t):]
    return "", pinyin

def parse_key2bpmf (buf):
    result = {}
    flag = False
    for line in buf.split(u'\n'):
        if flag == False and not "%keyname  begin" in line:
            continue
        elif flag == False:
            flag = True
            continue

        if "%keyname  end" in line:
            break
        key, bpmf = line.split ('  ', 2)
        result[key] = bpmf
    return result

def get_firstline (lines):
    for line in lines:
        if "%chardef  begin" in line:
            return lines.index (line)+1
    return 0

def get_pinyin (keys, key2bpmf):
    bpmf = ""
    for k in keys:
        if key2bpmf[k] == u"ˇ" or \
            key2bpmf[k] == u"ˋ" or \
            key2bpmf[k] == u"ˊ" or \
            key2bpmf[k] == u"˙":
            continue
        bpmf = bpmf + key2bpmf[k]
    return find_pinyin (bpmf)

def find_pinyin (bpmf):
    for key in bopomofo.bopomofo_pinyin_map.keys():
        if bpmf == unicode(key,'utf8'):
            return bopomofo.bopomofo_pinyin_map[key]
    return None

def bpmf2pinyin (bpmf):
    for tone in [u"ˇ", u"ˋ", u"ˊ", u"˙"]:
        bpmf = bpmf.replace (tone, "")
    bpmf_list = bpmf.split()
    pinyin = [find_pinyin (bpmf) for bpmf in bpmf_list]
    return pinyin

def read_phrases(cin, tsi):
    buf = file (tsi).read()
    buf = unicode(buf, "utf8")
    buf = buf.strip()
    lines = buf.split(u'\n')
    for line in buf.split(u'\n'):
        hanzi, freq, bpmf = line.split (u' ', 2)
        try:
            freq = float (freq) + 0.1
        except:
            continue
        pinyin = bpmf2pinyin (bpmf)
        if len(pinyin) == 0 or pinyin[0] == None: continue
        yield hanzi, freq, pinyin

'''
    buf = file(cin).read()
    buf = unicode(buf, "utf8")
    buf = buf.strip()
    key2bpmf = parse_key2bpmf (buf)
    lines = buf.split(u'\n')
    first = get_firstline (lines)
    for i in range (first, len(lines)):
        #hanzi, freq, flag, pinyin = lines[i].split(u' ', 2)
        if "%chardef  end" in lines[i]:
            break
        keys, hanzi = lines[i].split(u' ', 2)
        freq = float(0.1)
        pinyin = get_pinyin (keys, key2bpmf)
        if pinyin == None: continue
        yield hanzi, freq, [pinyin]
'''


def create_db(phone, tsi):
    # import sqlite3
    # con = sqlite3.connect("main.db")
    # con.execute ("PRAGMA synchronous = NORMAL;")
    # con.execute ("PRAGMA temp_store = MEMORY;")
    # con.execute ("PRAGMA default_cache_size = 5000;")
    print "PRAGMA synchronous = NORMAL;"
    print "PRAGMA temp_store = MEMORY;"
    print "PRAGMA default_cache_size = 5000;"


    sql = "CREATE TABLE py_phrase_%d (phrase TEXT, freq INTEGER, %s);"
    for i in range(0, 16):
        column = []
        for j in range(0, i + 1):
            column.append ("s%d INTEGER" % j)
            column.append ("y%d INTEGER" % j)
        print sql % (i, ",".join(column))
        # con.execute(sql % (i, column))
        # con.commit()

    records = list(read_phrases(phone, tsi))
    records.sort(lambda a, b: 1 if a[1] > b[1] else -1)
    records_new = []
    i = 0
    max_freq = 0.0
    for hanzi, freq, pinyin in records:
        if max_freq / freq <  1 - 0.001:
            max_freq = freq
            i = i + 1
        records_new.append((hanzi, i, pinyin))
    records_new.reverse()
    
    print "BEGIN;"
    insert_sql = "INSERT INTO py_phrase_%d VALUES (%s);"
    for hanzi, freq, pinyin in records_new:
        columns = []
        for py in pinyin:
            s, y = get_sheng_yun(py)
            try:
                s, y = pinyin_id[s], pinyin_id[y]
            except:
                print "hanzi: %s, pinyin: %s" % (hanzi, pinyin)
                sys.exit(1)
            columns.append(s)
            columns.append(y)
        values = "'%s', %d, %s" % (hanzi.encode("utf8"), freq, ",".join(map(str,columns)))
            
        sql = insert_sql % (len(hanzi) - 1, values)
        print sql
    print "COMMIT;"
    print "VACUUM;"

def main():
    create_db(sys.argv[1], sys.argv[2])
 
if __name__ == "__main__":
    main()
