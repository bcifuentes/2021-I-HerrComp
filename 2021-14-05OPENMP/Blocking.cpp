#include"Blocking.h"
#include<vector>

void FillMat(state_type &X,int N,int SEED){
  std::mt19937_64 gen(SEED);
    std::normal_distribution<double> dis(-100, 100);
  for (size_t ii = 0; ii < N; ii++){
    for (size_t jj = 0; jj < N; jj++){
      X[N*ii+jj] = dis(gen);
    }
  }
}


void MultMAT(state_type &A, state_type &B, state_type &C, int N){
  int n=std::pow(A.size(),0.5);
  if (N<=n){
    int NSIZE = n/N;

    std::vector<double> temp = {0.0};
    temp.resize(N*N);
 
    for (int kk=0; kk<NSIZE;++kk){
      for (int ll=0; ll<NSIZE;++ll){ 
	for (int ii=0; ii<N;++ii){
	  for (int jj=0;jj<N;++jj){
	    double suma=0.;
	    for(int b=0;b<N;++b){
	      for(int a=0;a<NSIZE;++a){
		suma=A[(ii+N*kk)*n+(b+N*a)]*B[(b+N*a)*n+(jj+N*ll)];
		temp[ii*N+jj]+=suma;
	      }
	    }
	  }
	}
	for(int ii=0;ii<N;++ii){
	  for(int jj=0;jj<N;++jj){
	    C[(ii+N*kk)*n+(jj+N*ll)]=temp[ii*N+jj];
	  }
	}     
	for(int ii=0; ii<temp.size();++ii){
	  temp[ii]=0;
	}
      }
    }
  }
}


void TransMAT(state_type &X,state_type &XT,int N){
  int n=std::pow(X.size(),0.5);
  if (N<=n){
    int NSIZE = n/N;

    std::vector<double> temp = {0.0};
    temp.resize(N*N);

    for (int kk=0; kk<NSIZE;++kk){
      for (int ll=0; ll<NSIZE;++ll){
	for (int ii=0; ii<N;++ii){
	  for (int jj=0;jj<N;++jj){
	    temp[ii*N+jj]=X[(jj+N*kk)*n+(ii+N*ll)];
	  }
	}
	for(int ii=0;ii<N;++ii){
	  for(int jj=0;jj<N;++jj){
	    XT[(ii+N*ll)*n+(jj+N*kk)]=temp[ii*N+jj];
	  }
	}
      }
    }
  }
}
