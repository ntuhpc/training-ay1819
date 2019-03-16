PROGRAM Data_Depend
  IMPLICIT NONE
  INCLUDE "omp_lib.h"
  INTEGER, PARAMETER :: N = 12000
  REAL, DIMENSION(N,N) :: AP, AS
  REAL :: x
  INTEGER :: i,j,k, check_error

! intialize the matrices
! AS is for serial version, AP for the parallel method.
  CALL random_number(AP)
  AS=AP
! and the constant
  CALL random_number(x)

! PARALLISE THIS SECTION

  DO k = 1, 5
     DO j = 2, N
        DO  i = 1, N
           AP(i,j) = AP(i,j-1) + x + REAL(k)
        END DO
     END DO
  END DO

! Serial version to compare

  DO k = 1, 5
     DO j = 2, N 
        DO i = 1, N 
           AS(i,j) = AS(i,j-1) + x + REAL(k)
        END DO
     END DO
  END DO

    
! TEST FOR SUCCESS 
! Compare results of parallel version with the serial results.
 
  check_error = 0
  DO i=1,N 
     DO j=1,N
        IF( AP(i,j).ne.AS(i,j) ) THEN
           check_error = 1
        END IF
    END DO
 END DO


 IF (check_error == 0) THEN
    WRITE(*,*) 'No error encountered with solution'
 ELSE
    WRITE(*,*) 'Error encountered with solution'
 END IF
    

END PROGRAM Data_Depend
