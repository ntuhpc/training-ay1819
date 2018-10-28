PROGRAM Mat_mul

  ! Calculates C=A*B, where A is a m*k matrix, B is a k*n matrix and C is a
  ! m*n matrix

  IMPLICIT NONE
  INCLUDE "omp_lib.h"
  INTEGER, PARAMETER :: n = 600, m = 600, k = 600, wd=selected_real_kind(10,200)
  ! change to wd=selected_real_kind(5) for single precision
  REAL(KIND=WD), DIMENSION(m,k) :: A
  REAL(KIND=WD), DIMENSION(k,n) :: B
  REAL(KIND=WD), DIMENSION(m,n) :: C, CS
  REAL(KIND=WD) ::  alpha, beta, parallel_start, parallel_end, serial_start, serial_end
  Real(KIND=WD) :: max_diff
  INTEGER :: i,j,l

  ! intialize the matrices  
  CALL random_number(A)
  CALL random_number(B) 
  CALL random_number(C)
  CS = C
  ! and the constants
  CALL random_number(alpha)
  CALL random_number(beta)

  parallel_start = OMP_GET_WTIME()

  ! PARALLELISE THIS LOOP NEST
  DO i = 1, n
     DO j = 1, m
        C(j,i) = beta*C(j,i) 
        DO  l = 1, k
           C(j,i) = C(j,i) + alpha*A(j,l)*B(l,i) 
        END DO
     END DO
  END DO

  parallel_end = OMP_GET_WTIME()

  serial_start = OMP_GET_WTIME()

  ! Serial version for comparison
  DO i = 1,n
     DO j = 1, m
        CS(j,i) = beta*CS(j,i) 
        DO  l = 1, k
           CS(j,i) = CS(j,i) + alpha*A(j,l)*B(l,i) 
        END DO
     END DO
  END DO

  serial_end = OMP_GET_WTIME()

  ! Compare the output to check the parallel version is correct
  max_diff = MAXVAL( ABS( CS - C ) )

  WRITE(*,*) 'Parallel version took ', parallel_end - parallel_start, ' seconds.'       
  WRITE(*,*) 'Serial version took ', serial_end - serial_start, ' seconds.'
  WRITE(*,*) 'Maximum difference in results is ', max_diff

END PROGRAM Mat_mul
