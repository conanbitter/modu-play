from PIL import Image
import os

BYTES_PER_LINE = 8

DESTINATION_DIR = "../src/"
RESOURCE_PREFIX = "IMG_"

outc = open(os.path.join(DESTINATION_DIR, "assets.c"), 'w')
outh = open(os.path.join(DESTINATION_DIR, "assets.h"), 'w')
outh.write(
    """#ifndef _ASSETS_H_
#define _ASSETS_H_

"""
)


def convert_name(name):
    res = []
    for symbol in name:
        if (symbol >= 'A' and symbol <= 'Z') or (symbol >= '0' and symbol <= '9'):
            res.append(symbol)
        elif symbol >= 'a' and symbol <= 'z':
            res.append(symbol.upper())
        else:
            res.append('_')
    return ''.join(res)


def convert_file(filename):
    img = Image.open(filename)
    mask = None
    is_transparent = False

    name = os.path.splitext(filename)[0]  # convert_name(os.path.splitext(filename)[0])
    if name.endswith("_t"):
        name = name[:-2]
        is_transparent = True
        mask = img

    name = RESOURCE_PREFIX + convert_name(name)

    img = img.convert('L')
    lines = img.height // 8
    array_size = img.width * lines
    if is_transparent:
        array_size *= 2
    array_size += 2

    outh.write(f"const unsigned char {name}[{array_size}];\n\n")
    outc.write(f"const unsigned char {name}[{array_size}] = {{\n")
    outc.write(f"    {img.width}, {lines},\n")

    bytes_accum = 0

    for row in range(lines):
        for col in range(img.width):
            line = 0
            for cb in range(8):
                if img.getpixel((col, row * 8 + cb)) > 128:
                    line |= 1 << cb
            if bytes_accum == 0:
                outc.write("    ")
            outc.write("0x{0:02X}, ".format(line))
            bytes_accum += 1
            if bytes_accum >= BYTES_PER_LINE:
                outc.write("\n")
                bytes_accum = 0

    if is_transparent:
        for row in range(lines):
            for col in range(img.width):
                line = 0
                for cb in range(8):
                    if mask.getpixel((col, row * 8 + cb))[3] > 128:
                        line |= 1 << cb
                if bytes_accum == 0:
                    outc.write("    ")
                outc.write("0x{0:02X}, ".format(line))
                bytes_accum += 1
                if bytes_accum >= BYTES_PER_LINE:
                    outc.write("\n")
                    bytes_accum = 0

    outc.write("};\n\n\n")


files = []
folder = os.getcwd()

for entry in os.listdir(folder):
    full_path = os.path.join(folder, entry)
    if os.path.isfile(full_path) and os.path.splitext(full_path)[1] == ".png":
        files.append(entry)

for filename in files:
    convert_file(filename)

outh.write("\n#endif\n")
outc.close()
outh.close()
