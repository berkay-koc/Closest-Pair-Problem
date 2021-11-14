#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
    int x, y;
};

struct point point1, point2;
float minVal;

float findMedian(struct point *points, int n);
float findDistance(struct point p1, struct point p2);
void insertionSort(struct point *points, int n);
void bruteForce(struct point *points, int n);
float splitAndCalculate(struct point *points, int n);
void comparePairs(struct point *leftPoints, struct point *rightPoints, int leftLength, int rightLength, float median);

int main(){
	FILE *inputFile;
	char fileName[20];
	int n=0, temp, i=0;
	struct point *points;
	strcpy(fileName, "sample.txt");
	
	if ((inputFile = fopen (fileName, "r+")) == NULL){
        printf("can't open the file");
        return 0;
    }
    
	while(!feof(inputFile)){
    	fscanf(inputFile,"%d %d\n", &temp, &temp);
    	n++;
	}
	printf("number of lines in file: %d\n", n);
	
	points = (struct point *)malloc(sizeof(struct point) * n);
	
	fclose(inputFile);
	
	if ((inputFile = fopen (fileName, "r+")) == NULL){
        printf("can't open the file");
        return 0;
    }
    
    while(!feof(inputFile)){
    	fscanf(inputFile,"%d %d\n", &points[i].x, &points[i].y);
    	i++;
	}
	fclose(inputFile);
	
    insertionSort(points, n);
    printf("Sorted arrays of x,y");
	for(i=0; i<n; i++){
		printf("%d %d\n", points[i].x, points[i].y);
	}
	float a = findMedian(points, n);
	printf("%f\n\n", a);
	
	minVal = findDistance(points[0], points[1]);
	splitAndCalculate(points, n);
	printf("Minimum distance is between pairs (%d, %d) and (%d, %d). Minimum distance is: %f\n",point1.x, point1.y, point2.x, point2.y, minVal);
	
	return 0;
}

void insertionSort(struct point *points, int n){
    int i, j;
    struct point key;
    for (i = 1; i < n; i++){
        key = points[i];
        j = i - 1;
		
        while (j >= 0 && points[j].x > key.x){
            points[j + 1] = points[j];
            j = j - 1;
        }
        points[j + 1] = key;
    }
}

float findDistance(struct point p1, struct point p2){
	printf("x1: %d y1: %d\nx2: %d y2: %d\n\n", p1.x, p1.y, p2.x, p2.y);
	return sqrt((p1.x  - p2.x)*(p1.x  - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float findMedian(struct point *points, int n){
	if(n%2 == 1){
		return points[n/2].x;
	}
	else{
		float fl = (n-1)/2;
		float cl = (n/2);
		return (float)(points[(int)fl].x + points[(int)cl].x)/2;
	}
}

float splitAndCalculate(struct point *points, int n){
	int i, leftLength=0, rightLength=0;
	float a, minDistance, median;
	struct point *leftPoints;
	struct point *rightPoints;
	insertionSort(points, n);
	if(n%2 == 1){
		leftPoints = (struct point *) malloc(sizeof(struct point) * (n/2));
		leftLength = n/2;
		rightPoints = (struct point *) malloc(sizeof(struct point) * (n+1)/2);
		rightLength = (n+1)/2;
	}
	else{
		leftPoints = (struct point *) malloc(sizeof(struct point) * (n/2));
		leftLength = n/2;
		rightPoints = (struct point *) malloc(sizeof(struct point) * (n/2));
		rightLength = (n+1)/2;
	}
	if(n<=3){
		bruteForce(points, n);
	}
	else{
		median = findMedian(points, n);
		for(i=0; i<leftLength; i++){
			leftPoints[i].x = points[i].x;
			leftPoints[i].y = points[i].y;
			printf("leftPoints[%d]: (%d,%d)\n",i, leftPoints[i].x,leftPoints[i].y);	
		}
		for(i=0; i<rightLength; i++){
			rightPoints[i].x = points[i+leftLength].x;
			rightPoints[i].y = points[i+leftLength].y;
			printf("rightPoints[%d]: (%d,%d)\n",i, rightPoints[i].x,rightPoints[i].y);	
		}
		printf("left pair length: %d\n", leftLength);
		printf("right pair length: %d\n", rightLength);
		
		printf("(Goes to the left pair)\n");
		splitAndCalculate(leftPoints, leftLength);
		printf("(Goes to the right pair)\n");
		splitAndCalculate(rightPoints, rightLength);
		comparePairs(leftPoints, rightPoints, leftLength, rightLength, median);
	}
	return minDistance;
}

void bruteForce(struct point *points, int n){
	float dist1, dist2, dist3;
	struct point temp1, temp2;
	if(n == 3){
		printf("comparing (%d, %d),(%d, %d),(%d, %d)\n", points[0].x, points[0].y,  points[1].x, points[1].y, points[2].x, points[2].y);
		dist1 = findDistance(points[0], points[1]);
		printf("distance between (%d, %d) and (%d, %d) = %f\n", points[0].x, points[0].y,  points[1].x, points[1].y, dist1);
		dist2 = findDistance(points[0], points[2]);
		printf("distance between (%d, %d) and (%d, %d) = %f\n", points[0].x, points[0].y,  points[2].x, points[2].y, dist1);
		dist3 = findDistance(points[1], points[2]);
		printf("distance between (%d, %d) and (%d, %d) = %f\n", points[1].x, points[1].y,  points[2].x, points[2].y, dist1);
		if(dist2 < dist1){
			if(dist2 < dist3){
				temp1 = points[0];
				temp2 = points[2];
				dist1 = dist2;
			}
			else{
				temp1 = points[1];
				temp2 = points[2];
				dist1 = dist3;
			}
		}
		else if(dist3 < dist1){
			temp1 = points[1];
			temp2 = points[2];
			dist1 = dist3;
		}
		else{
			temp1 = points[0];
			temp2 = points[1];
		}
	}
	else{
		printf("\n\ncomparing (%d, %d), (%d, %d)\n", points[0].x, points[0].y,  points[1].x, points[1].y);
		temp1 = points[0];
		temp2 = points[1];
		dist1 = findDistance(points[0], points[1]);
		printf("distance between (%d, %d) and (%d, %d) = %f\n", points[0].x, points[0].y,  points[1].x, points[1].y, dist1);
	}
	if(dist1 < minVal){
		point1 = temp1;
		point2 = temp2;
		minVal = dist1;
		printf("minimum distance is updated!\n");
	}
}

void comparePairs(struct point *leftPoints, struct point *rightPoints, int leftLength, int rightLength, float median){
	int i, j;
	struct point *tempArr;
	for(i=0; i<leftLength; i++){
		for(j=0; j<rightLength; j++){
			if(leftPoints[i].x > (median-minVal) && rightPoints[j].x < (median+minVal)){
				if(findDistance(leftPoints[i], rightPoints[j]) < minVal){
					printf("comparing (%d, %d), (%d, %d)\n", leftPoints[i].x, leftPoints[i].y, rightPoints[j].x, rightPoints[j].y);
					minVal = findDistance(leftPoints[i], rightPoints[j]);
					point1 = leftPoints[i];
					point2 = rightPoints[j];
					printf("minimum distance is updated!\n");
				}
			}
		}
	}
}
