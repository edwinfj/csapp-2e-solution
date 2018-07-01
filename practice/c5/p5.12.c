void psum(float a[], float p[], int n) {
	float psum = 0;
	for (int i = 0; i < n; ++i) {
		psum += a[i];
		p[i] = psum;
	}
}
