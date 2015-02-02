#!/usr/bin/python
# Utility generates files with random quasi-electrical data.
#
# Usage: gen_data.py output_file_name
#
# File contains little endian binary data. Specifically:
# 1. 16 bytes MD5 hash of the rest of the file for integrity checking
# 2. A series of blocks of data, each containing:
# 2a. An unsigned 32bit integer containing the number of records in the block
# 2b. The records:
# 2bi. Each record contains two IEEE 754 float32 numbers, the first for voltage
#      and the second for current.
#
# Steve English <steve.english@navetas.com>

import sys
import struct
import random

import hashlib
def writeAndHash( running_hash, output_file, data ):
    running_hash.update( data )
    output_file.write( data )

BLOCK_COUNT_RANGE = (50000, 250000) #Both ends inclusive
BLOCK_SIZE_RANGE = (0, 20) #Both ends inclusive
MAX_VOLTAGE = 330
MAX_CURRENT = 10

if len(sys.argv) < 2:
    print "Usage: %s output_file_name" % sys.argv[0]
    sys.exit(-1)

#0. Dump out a binary file
output = open( sys.argv[1], "wb" )

#1. The hash
hasher = hashlib.md5()
assert( hasher.digest_size == 16 )
#Will have to fill this in at the end - for now just a placeholder
output.write( "\x00" * hasher.digest_size )

#2. Some blocks
count = 0
for i in range( random.randint(*BLOCK_COUNT_RANGE) ):
    #3. Block size
    records = random.randint( *BLOCK_SIZE_RANGE )
    writeAndHash( hasher, output, struct.pack( "<I", records ) )
    
    #Records
    for j in range( records ):
        voltage = random.random() * 330
        current = random.random() * 10
	print current

        #Track the average
        count += 1
        
        writeAndHash( hasher, output, struct.pack( "<ff", voltage, current ) )

#3. Put the hash on the beginning
output.seek( 0 )
output.write( hasher.digest() )

print "Record count: %d" % count
