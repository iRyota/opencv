#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/* グローバル変数 */
IplImage *img = 0;
IplImage *src_img = 0;

int
main (int argc, char *argv[])
{
  // 画像データの読み込み
  if (argc >= 2)
    src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;

  // 画像領域を確保し，初期化する
  img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 3);

  // 平滑化処理
  cvSmooth(src_img, img, CV_GAUSSIAN, 9, 9, 0, 0);

  // ウィンドウ作成・表示
  cvNamedWindow ("Filtered Image", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Filtered Image", img);
  cvNamedWindow ("Source Image", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Source Image", src_img);

  cvWaitKey (0);

  cvDestroyWindow ("Image");
  cvReleaseImage (&img);

  return 0;
}

