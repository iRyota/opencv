all: sample1 binarization edge faceTracking camera camera_bin camera_nega direct gray binary

sample1: sample1.c
	gcc -o sample1 sample1.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

binarization : binarization.c
	gcc -o binarization binarization.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

edge : edge.c
	gcc -o edge edge.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

faceTracking : faceTracking.c
	gcc -o faceTracking faceTracking.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

camera : camera.c
	gcc -o camera camera.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

camera_bin : camera_bin.c
	gcc -o camera_bin camera_bin.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

camera_nega : camera_nega.c
	gcc -o camera_nega camera_nega.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

direct : direct.c
	gcc -o direct direct.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

gray : gray_img.c
	gcc -o gray gray_img.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

binary : binary_img.c
	gcc -o binary binary_img.c `pkg-config opencv --cflags` `pkg-config opencv --libs`
