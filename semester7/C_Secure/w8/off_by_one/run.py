outfile = open("b2.bin", "wb")
outfile.write(
    b"12345678"
    + b"12345678"
    + b"12345678"
    + b"12345678"
    + b"12345678"
    + b"\x98\x11\x40\x00\x00\x00\x00\x00"
)
outfile.close()
