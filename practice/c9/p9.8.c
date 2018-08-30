// fit first
staic void *find_fit(size_t asize)
{
	void *bp = heap_listp;
	size_t cur_alloc, cur_size;

	do {
		bp = NEXT_BLKP(bp);
		cur_alloc = GET_ALLOC(HDRP(bp));
		cur_size = GET_SIZE(HDRP(bp));
		if (cur_size == 0 && cur_alloc == 1) {
			// couldn't find a fit
			bp = NULL;
			break;
		}
	} while (cur_alloc == 1 || cur_size < asize);

	return bp;
}
