.name "champion"
.comment ""

protect:
ld %42991616, r10
ld %3849, r12
st r10, -40
st r12, -36
st r10, -34
st r12, -34
core:
live %1
fork %:protect
st r1, -7
ld :core, r5
ld 5, r3
st r3, 256
st r5, 256
ld %0, r16
zjmp %220
