// next-fit search
staic void *find_fit(size_t asize)
{
	static void *s_bp = heap_listp;
	size_t cur_alloc, cur_size;

	do {
		s_bp = NEXT_BLKP(s_bp);
		cur_alloc = GET_ALLOC(HDRP(s_bp));
		cur_size = GET_SIZE(HDRP(s_bp));
		if (cur_size == 0 && cur_alloc == 1) {
			// epiloge
			return NULL;
		}
	} while (cur_alloc == 1 || cur_size < asize);

	return s_bp;
}
