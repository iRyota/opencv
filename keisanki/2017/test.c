#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/* グローバル変数 */
IplImage *src_img = 0;
int a=2;
IplImage img_hdr,*dst_img;
CvMat mat_hdr;

/* プロトタイプ宣言 */
void on_mouse (int event, int x, int y, int flags, void *param);

int main (int argc, char *argv[])
{
  int c;
  CvCapture *capture = 0;

  // (1)指定された番号のカメラに対するキャプチャ構造体を作成する
  capture = cvCreateCameraCapture(0);
  src_img = cvQueryFrame (capture);

  // ウィンドウを作成し,マウスイベントに対するコールバック関数を登録する
  cvNamedWindow ("dst", CV_WINDOW_AUTOSIZE);
  cvNamedWindow ("src", CV_WINDOW_AUTOSIZE);
  cvSetMouseCallback ("dst", on_mouse, &a);

  while(1){
    printf("%d\n",a);
    switch(a){
      case 1:
        // 画像形状の変更を行う
        cvReshape (src_img, &mat_hdr, 1, 0);
        dst_img = cvGetImage (&mat_hdr, &img_hdr);
        break;
      case 2:dst_img=cvCloneImage(src_img);
        break;
    }
    cvShowImage ("dst", dst_img);
    cvShowImage ("src", src_img);
    // 'Esc' キーが押された場合に終了する
    c = cvWaitKey (0);
    if (c == '\x1b')
      break;
  }
  cvDestroyWindow ("dst");
  cvDestroyWindow ("src");
  cvReleaseImage (&src_img);
  cvReleaseImage (&dst_img);
  return 0;
}
/* コールバック関数 */
void on_mouse (int event, int x, int y, int flags, void *param)
{
  // マウスイベントを取得
  switch (event) {
    case CV_EVENT_LBUTTONDOWN:
      a=1;
      break;
    case CV_EVENT_RBUTTONDOWN:
      a=2;
      break;
  }
}
