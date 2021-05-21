#!/usr/bin/env python3

"""program to read binary file (32 bit)"""

# import modules
import struct
import sys
import argparse


# program
def ReadFile(file_object):
    f_i = file_object

    line_number = 0
    word_index = 0
    word = [0] * 4
    mem_size = offset = 8192

    while True:
        try:
            # read 4 bytes at a time, convert to unsigned int
            word[word_index], = (struct.unpack('I', f_i.read(4)))
            if line_number == 3:
                link_id = word[3] & 0xff
                packet_c = (word[3] >> 8) & 0xffff
                cru_id = (word[3] >> 16) & 0xfff
                stop_bit = word[3] & 0xff
                offset = word[2] & 0xffff
                mem_size = (word[2] >> 16)
                fee_id = word[1] & 0xffff
                priority_bit = (word[1] >> 16) & 0xff
                header_version = word[0] & 0xff
                header_size = (word[0] >> 8) & 0xff
                block_length = (word[0] >> 16) & 0xffff
                msg = "CRU ID: {:#05x} FEE ID: {} Link ID: {} packet count: {} stop bit: {} offset: {} memSize: {} header version: {}, header size: {} block length: {} priority bit {}"
                print(msg.format(cru_id, fee_id, link_id, packet_c, stop_bit, offset, mem_size, header_version, header_size, block_length, priority_bit))

            if line_number == 7:
                hb_orbit = word[1]
                trg_orbit = word[0]
                msg = "HB ORBIT: {} TRG ORBIT {}"
                print(msg.format(hb_orbit, trg_orbit))

            if line_number == 11:
                trg_type = word[1]
                hb_bc = (word[0] >> 16) & 0xfff
                trg_bc = word[0] & 0xfff
                msg = "HB BC: {} TRG BC {}"
                print(msg.format(hb_bc, trg_bc))
                print("-----------------------------------")

            #if (line_number+1) % 4 == 0 and line_number not in [3,7,11]:
                #print("{:4d}) {:#010x} {:#010x} {:#010x} {:#010x}".format((line_number), word[3], word[2], word[1], word[0]))
            
            word_index = (word_index + 1) % 4
            line_number = (line_number + 1) % 2048

            if (line_number == (offset / 4)):
                line_number = 0
        except Exception:
            break


# define main
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', nargs='?')
    parser.add_argument("-s", "--offset", type=int, required=False,
                        help="Byte offset for the data decoding to seek to. NOTE: not supported without input file (i.e. with input in stdin)",
                        default=0)
    args = parser.parse_args()
    offset = args.offset
    if args.filename:
        f_i = open(args.filename, 'rb')
        if offset != 0:
            f_i.seek(offset)
    elif not sys.stdin.isatty():
        f_i = sys.stdin.buffer
    else:
        parser.print_help()
        exit(0)

    ReadFile(f_i)
    # close the file
    f_i.close()


if __name__ == '__main__':
    main()
