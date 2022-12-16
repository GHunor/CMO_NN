//
// Created by ghuno on 2021-11-24.
//

#ifndef TESTER_CV_H
#define TESTER_CV_H

namespace cv {
#define CV_8U 0
#define WINDOW_NORMAL 5

    class Mat {
    public:
        int cols,rows;
        int* initial_col;
        int** matrix;

        Mat() : cols(0), rows(0) {}
        Mat(int cols, int rows) : cols(cols), rows(rows) {
            matrix = new int*[cols];
            for(int i=0;i<cols;i++){
                matrix[cols] = new int[rows];
            }
            initial_col = matrix[0];
        }
        Mat(int cols, int rows, int v) : cols(cols), rows(rows) {
            matrix = new int*[cols];
            for(int i=0;i<cols;i++){
                matrix[cols] = new int[rows];
                for(int j=0; i<rows;i++){
                    matrix[cols][j] = 0;
                }
            }
            initial_col = matrix[0];
        }

        Mat &col(int idx);

        static Mat& zeros(int a, int b, int c){
            Mat* m = new Mat(a,b, 0);
            return *m;
        };

        template<class T>
        int &at(int i, int i1) {
            return matrix[i][i1];
        }

        void copyTo(Mat);

        int getCols() const {
            return cols;
        }

        void setCols(int cols) {
            Mat::cols = cols;
        }

        Mat &operator=(const int &idx) {
            cols = idx;
            return *this;
        }


    };
    void waitKey(int i) {

    }
    void namedWindow(const char *string, int i) {

    }
    void imshow(const char *string, Mat mat);
}
#endif //TESTER_CV_H
