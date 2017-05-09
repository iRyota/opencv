#include <cv.h>
#include <highgui.h>
#include <ctype.h>

int
main (int argc, char **argv)
{
  CvCapture *capture = 0;
  IplImage *frame = 0;
  IplImage *src_img_gray = 0, *tmp_img1 = 0;
  int c;

  // (1)指定された番号のカメラに対するキャプチャ構造体を作成する
  capture = cvCreateCameraCapture(0);

  // (2)表示用ウィンドウをの初期化
  cvNamedWindow ("Capture", CV_WINDOW_AUTOSIZE);

  while (1) {
    // (3)カメラから画像をキャプチャする
    frame = cvQueryFrame (capture);
    // (3)-2 カメラ画像を加工する
    tmp_img1 = cvCreateImage (cvGetSize(frame)  ,IPL_DEPTH_8U, 1);
    src_img_gray = cvCreateImage (cvGetSize(frame)  ,IPL_DEPTH_8U, 1);
    cvCvtColor (frame, src_img_gray, CV_BGR2GRAY);
    cvThreshold (src_img_gray, tmp_img1, 90, 255, CV_THRESH_BINARY);
    
    // (4) カメラ画像の表示
    cvShowImage ("Capture", src_img_gray);
    cvShowImage ("Capture", tmp_img1    );
    cvReleaseImage (&src_img_gray);
    cvReleaseImage (&tmp_img1);
    // (5) 2msecだけキー入力を待つ
    c = cvWaitKey (2);
    if (c == '\x1b') // Escキー
      break;
  }

  cvReleaseCapture (&capture);
  cvDestroyWindow ("Capture");

  return 0;
}
