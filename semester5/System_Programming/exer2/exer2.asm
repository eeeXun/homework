test     start   1000
first    jsub    rdint         read a,n,m
         lda     buffer
         sta     na
         jsub    rdint
         lda     buffer
         sta     nn
         jsub    rdint
         lda     buffer
         sta     nm
.   ans = a - (a/m)*m
         lda     na
         div     nm
         mul     nm
         sta     buffer
         lda     na
         sub     buffer
         sta     ans
.   mod
         jsub    mod
..........
         rsub
na       resw    1
nn       resw    1
nm       resw    1
zero     word    0
one      word    1
three    word    3
ans      resw    1
buffer   resw    1
.
.   subroutine to get a^n%m
.
mod      lda     nn
         comp    one
         jeq     wdint
.   ans = ans*a
         lda     ans
         mul     na
         sta     ans
.   regA = ans/m
         div     nm
.   buffer = (ans/m)*m
         mul     nm
         sta     buffer
.   ans - buffer = ans
         lda     ans
         sub     buffer
         sta     ans
.   n = n-1
         lda     nn
         sub     one
         sta     nn
         j       mod
.
.   subroutine to read 3-byte big-endian int into A
.
rdint    ldx     zero
         lda     zero
rloop    td      input
         jeq     rloop
         rd      input
         stch    buffer,x
         tix     three
         jlt     rloop
         rsub
input    byte    x'f3'
.
.   subroutine to write 3-byte big-endian from A
.
wdint    ldx     zero
wloop    td      output
         jeq     wloop
         ldch    ans,x
         wd      output
         tix     three
         jlt     wloop
         rsub
.
output   byte    x'06'
         end     first
