.name "champion"
.comment ""

core:
live %1
fork %:core
st r1, -7
ld :core, r5
ld 5, r3
st r3, 256
st r5, 256
ld %0, r16
zjmp %220
