/*
 * bitstream.h: generic bitstream parsing
 *
 * See the main source file 'xineliboutput.c' for copyright information and
 * how to reach the author.
 *
 * $Id: bitstream.h,v 1.3 2009/02/14 20:44:15 phintuka Exp $
 *
 */

#ifndef _XINELIBOUTPUT_BITSTREAM_H_
#define _XINELIBOUTPUT_BITSTREAM_H_



#ifdef NOCACHE

typedef struct {
  const uint8_t *data;
  int            count; /* in bits */
  int            index; /* in bits */
} br_state;

#define BR_INIT(data,bytes) { (data), 8*(bytes), 0 }

#define BR_EOF(br) ((br)->index >= (br)->count)

static __inline void br_init(br_state *br, const uint8_t *data, int bytes)
{
  br->data  = data;
  br->count = 8*bytes;
  br->index = 0;
}

static __inline int br_get_bit(br_state *br)
{
  
	int r = 0;
	if(br->index >= br->count)
    return 1; /* -> no infinite colomb's ... */

  r = (br->data[br->index>>3] >> (7 - (br->index&7))) & 1;
  br->index++;
  return r;
}

static __inline uint32_t br_get_bits(br_state *br, uint32_t n)
{
  uint32_t r = 0;
  while(n--)
    r = r | (br_get_bit(br) << n);
  return r;
}

#define br_skip_bit(br) br_skip_bits(br,1)

static __inline void br_skip_bits(br_state *br, int n)
{
  br->index += n;
}


#else /* NOCACHE */


#endif /* NOCACHE */


#define br_get_u8(br)         br_get_bits(br, 8)
#define br_get_u16(br)        ((br_get_bits(br, 8)<<8) | br_get_bits(br, 8))

static __inline uint32_t br_get_ue_golomb(br_state *br)
{
  int n = 0;
  while (!br_get_bit(br) && n < 32)
    n++;
  return n ? ((1<<n) - 1) + br_get_bits(br, n) : 0;
}

static __inline int32_t br_get_se_golomb(br_state *br)
{
  uint32_t r = br_get_ue_golomb(br) + 1;
  return (r&1) ? -(r>>1) : (r>>1);
}

static __inline void br_skip_golomb(br_state *br)
{
  int n = 0;
  while (!br_get_bit(br) && n < 32)
    n++;
  br_skip_bits(br, n);
}

#define br_skip_ue_golomb(br) br_skip_golomb(br)
#define br_skip_se_golomb(br) br_skip_golomb(br)


#endif /* _XINELIBOUTPUT_BITSTREAM_H_ */
