"""Create a deterministic synthetic RGBA image for viewer smoke tests."""
import struct
import zlib
from pathlib import Path
width,height=960,640
def chunk(name,data):
    return struct.pack('>I',len(data))+name+data+struct.pack('>I',zlib.crc32(name+data)&0xffffffff)
rows=[]
for y in range(height):
    row=bytearray([0])
    for x in range(width):
        if (x-740)**2+(y-150)**2<60**2: pixel=(247,238,210,255)
        elif y>height-abs(x-430)*.60-50: pixel=(65,96,113,255)
        elif y>height-abs(x-230)*.70-150: pixel=(151,184,205,255)
        else: pixel=(110,160+int(y/20),196,255)
        row.extend(pixel)
    rows.append(row)
data=b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',width,height,8,6,0,0,0))+chunk(b'IDAT',zlib.compress(b''.join(rows)))+chunk(b'IEND',b'')
target=Path('build/fixtures/mountain-view.png');target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(data)
print(target)
