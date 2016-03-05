/*
 * @file       rm_tx.c
 * @brief      Definitions used by rsync transmitter (A).
 * @author     Piotr Gregor <piotrek.gregor at gmail.com>
 * @version    0.1.2
 * @date       2 Jan 2016 11:19 AM
 * @copyright  LGPLv2.1
 */


#include "rm_tx.h"


int
rm_tx_local_push(const char *x, const char *y,
        uint32_t L, rm_push_flags flags)
{
	int         err;
	FILE        *f_x, *f_y, *f_z;
	int         fd_x, fd_y, fd_z;
	struct      stat	fs;
	uint32_t    x_sz, y_sz, blocks_n, blocks_n_exp;

	(void) x_sz;
    f_x = f_y = f_z = NULL;
	TWDEFINE_HASHTABLE(h, RM_NONOVERLAPPING_HASH_BITS);

    f_x = fopen(x, "rb");
	if (f_x == NULL)
        return -1;

	f_y = fopen(y, "rb");
	if (f_y == NULL)
	{
        if (flags & RM_BIT_0) /* force create if doesn't exist? */
        {
            f_z = fopen(y, "wb+");
            if (f_z == NULL)
            {
                err = -2;
                goto err_exit;
            }
        } else {
		    err = -3;
            goto err_exit;
	    }
    }

	// get file size
	fd_x = fileno(f_x);
	if (fstat(fd_x, &fs) != 0)
	{
		err = -4;
		goto err_exit;
	}
	x_sz = fs.st_size; 
	if ( f_y != NULL)
    {
        fd_y = fileno(f_y);
	    if (fstat(fd_y, &fs) != 0)
	    {
		    err = -5;
		    goto err_exit;
	    }
	    y_sz = fs.st_size;
	    /* split @y file into non-overlapping blocks
        * and calculate checksums on these blocks
        * expected number of blocks */
	    blocks_n = y_sz / L + (y_sz % L ? 1 : 0);
    }
	return 0;

err_exit:
	if (f_x != NULL) fclose(f_x);
	if (f_y != NULL) fclose(f_y);
    if (f_z != NULL) fclose(f_z);
	return err;
}

int
rm_tx_remote_push(const char *x, const char *y,
		struct sockaddr_in *remote_addr,
		uint32_t L)
{
	return 0;
}
