all: sample1 binarization edge faceTracking camera camera_bin camera_nega direct gray binary extract edge_detect trackbar mouse_event bin_trackbar

# kadai1
sample1: ./kadai1/sample1.c
	cd kadai1; gcc -o sample1 sample1.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

# kadai2
binarization : ./kadai2/binarization.c
	cd kadai2; gcc -o binarization binarization.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

edge : ./kadai2/edge.c
	cd kadai2; gcc -o edge edge.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

faceTracking : ./kadai2/faceTracking.c
	cd kadai2; gcc -o faceTracking faceTracking.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

# kadai3
camera : ./kadai3/camera.c
	cd kadai3; gcc -o camera camera.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

camera_bin : ./kadai3/camera_bin.c
	cd kadai3; gcc -o camera_bin camera_bin.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

camera_nega : ./kadai3/camera_nega.c
	cd kadai3; gcc -o camera_nega camera_nega.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

# kadai4
direct : ./kadai4/direct.c
	cd kadai4; gcc -o direct direct.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

gray : ./kadai4/gray_img.c
	cd kadai4; gcc -o gray gray_img.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

binary : ./kadai4/binary_img.c
	cd kadai4; gcc -o binary binary_img.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

extract : ./kadai4/color_extraction.c
	cd kadai4; gcc -o extract color_extraction.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

edge_detect : ./kadai4/edge_detection.c
	cd kadai4; gcc -o edge_detect edge_detection.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

# kadai5
trackbar : ./kadai5/trackbar.c
	cd kadai5; gcc -o trackbar trackbar.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

mouse_event : ./kadai5/mouse_event.c
	cd kadai5; gcc -o mouse_event mouse_event.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

bin_trackbar : ./kadai5/binary_trackbar.c
	cd kadai5; gcc -o bin_trackbar binary_trackbar.c `pkg-config opencv --cflags` `pkg-config opencv --libs`

