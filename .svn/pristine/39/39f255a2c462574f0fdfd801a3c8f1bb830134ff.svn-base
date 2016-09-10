import sys
import re
import math

events = []
pattern = 'Time=([0-9]*).*pitch=([0-9]*).*vol=([0-9]*)'
for line in sys.stdin:
    m = re.search(pattern, line)
    if m:
        events.append((int(m.group(1)), int(m.group(2)), int(m.group(3))))

def note_to_freq(note):
    return int(2.0**((note - 69) / 12.0) * 440)

c = 0
for i in range(len(events) - 1):
    time = events[i+1][0] - events[i][0]
    pitch = note_to_freq(events[i][1])
    vol = events[i][2]
    
    if time <= 0:
        continue
    
    print '{%6d, %4d, %4d},' % (time, pitch, vol),
    
    c += 1
    if c % 4 == 0:
        print
