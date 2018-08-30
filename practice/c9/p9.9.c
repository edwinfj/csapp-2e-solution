static void place(void *bp, size_t asize)
{
	size_t size = GET_SIZE(bp);
	size_t rsize = size - asize;
	
	// overhead + alignment req.
	if (rsize >= 2 * DSIZE) {
		// enough space, split
		PUT(HDRP(bp), PACK(asize, 1));
		PUT(FTRP(bp), PACK(asize, 1));	
		PUT(HDRP(NEXT_BLKP(bp)), PACK(rsize, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(rsize, 0));
	} else {
		// not enough space, no split
		PUT(HDRP(bp), PACK(size, 1));
		PUT(FTRP(bp), PACK(size, 1));
	}

}
