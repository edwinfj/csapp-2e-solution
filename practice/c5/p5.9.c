void merge(int src1[], int src2[], int dest[], int n) {
  int i1 = 0;
  int i2 = 0; 
  int id = 0;
  while (i1 < n && i2 < n) {
	int s1 = src1[i1];
	int s2 = src2[i2];
    int test1 = s1 < s2;
    dest[id++] = test1 ? s1 : s2;
    i1 += test1;
    i2 += 1 - test1;
  }
}
