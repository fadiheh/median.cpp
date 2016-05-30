// Copyright (C) 2014 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>

#include <stdio.h>
#include <stdlib.h>
#include "image.h"

typedef unsigned char elem_type ;

elem_type kth_smallest(elem_type a[], int n, int k)
{
	int i,j,l,m ;
	elem_type x, t ;
	l=0 ; m=n-1 ;
	while (l<m) {
		x=a[k] ;
		i=l ;
		j=m ;
		do {
			while (a[i]<x) {
				i++ ;
			}
			while (x<a[j]) {
				j-- ;
			}
			if (i<=j) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;				
				i++ ;	
				j-- ;
			}
		} while (i<=j) ;
		if (j<k) {
			l=i ;
		}
		if (k<i) {
			m=j ;
		}
	}
	return a[k] ;
}
#define median(a,n) kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)))


void medianFilter(const unsigned char input[][HEIGHT], unsigned char output[][HEIGHT], unsigned int width, unsigned int height)
{

    //TODO: put your implementation here
	unsigned char window[9];
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if ( i == 0 || j == 0 || i == WIDTH || j == HEIGHT) {
				output[i][j] = 0;			
			}
			else {
				for(int k = 0; k < 3; k++) {
					window[k*3] = input[i-1+k][j-1];
					window[k*3+1] = input[i-1+k][j];
					window[k*3+2] = input[i-1+k][j+1];
				}
				output[i][j] = median(window,9);
			}
		}
	}
}

