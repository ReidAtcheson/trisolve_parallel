#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <cassert>
extern "C" {
  void strsv_(char* uplo,char* trans,char* diag,int* N,float* A,int* lda,float* x,int* incx);
}

void make_triangular_matrix(int N,float* A);
void make_rhs(int N,float* x);
void check_soln(int N,float* x);



int main(int arg,char** argv){
  using std::chrono::steady_clock;
  using std::chrono::duration;
  using std::chrono::duration_cast;
  /*Initialize parameters to BLAS triangular solve.*/
  char uplo='U';
  char trans='N';
  char unit='N';
  int N=10000;
  int lda=N;
  int incx=1;
  std::vector<float> A(N*N,0.0);
  std::vector<float> x(N,0.0);
  /*Do a warmup call to BLAS before timing.*/
  make_triangular_matrix(N,&A[0]);
  make_rhs(N,&x[0]);
  strsv_(&uplo,&trans,&unit,&N,&A[0],&lda,&x[0],&incx);

  make_triangular_matrix(N,&A[0]);
  make_rhs(N,&x[0]);
  steady_clock::time_point start = steady_clock::now();
  strsv_(&uplo,&trans,&unit,&N,&A[0],&lda,&x[0],&incx);
  steady_clock::time_point stop = steady_clock::now();
  duration<double> tspan=duration_cast<duration<double>>(stop-start);
  check_soln(N,&x[0]);
  std::cout<<"Time to compute triangular solve: "<<(tspan.count())<<std::endl;


}

/**
 * Make upper triangular matrix with all 1s
 */
void make_triangular_matrix(int N,float* A){
  for(int r=0;r<N;r++){
    for(int c=0;c<N;c++){
      int id=r+c*N;
      if(c>=r){
        A[id]=1.0;
      }
      else{
        A[id]=0.0;
      }
    }
  }
}

/**
 * Makes a vector x such that inv(A)*x is a vector of all 1s
 * (easy to check that it's right)
 */
void make_rhs(int N,float* x){
  for(int r=0;r<N;r++){
    x[r]=float(N-r);
  }
}

/**
 * Checks that triangular solve output is correct
 */
void check_soln(int N,float* x){
  for(int r=0;r<N;r++){
    assert(std::abs(x[r]-1.0)<1e-5);
  }
}
