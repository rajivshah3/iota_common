/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "common/helpers/digest.h"
#include "common/helpers/pow.h"
#include "utils/system.h"

static tryte_t const *const TX_TRYTES = (tryte_t*)
    "XYIUIABLAEBBFCTMDCGPVNCQELHIEBVNRPWBSCABWRAVGVOVMFEHWJCUILYIXOPJNASEOHXP"
    "JBXFNHHSWEKEGEEFSAZDENWMOAXGJCQZQDGSTTMNQPYJBLRVY9T9HSQNXWYCSMLEXVWCASQ9"
    "MHPMBZ9PSSZEKCXYLDYKTOVAWQXOTGMWHUIACLUTAIKUIXZND9YMQKZBTIWOUIVQWTSBNVDC"
    "UWYP9HDMQPTXWEQYXVEOFXVGQSBHGHMKVFZZQIALVLMINZGNLEAOCQZFHPTQTQXGZQJLTBFP"
    "LWTESFYOJNJGJRYWHPEBSPSXEWCITXBJBMXDFCUDUKKGZMDOOPIBJLC9GPIBTLVQWPGTADEX"
    "NI9SWJNJXKXIJCPMICHBIFRXVWNJDP9BDELH9NOMJKGEBOCLWEXPEBFBWQLHFWQVCFIPVUXN"
    "REWXTCTFQHZYTMSUXQZTJQOWZZZCFIJ9NFXVSDFEXLODNJFREDOQ9WLLQAKRYKUCGUYEFICO"
    "LCKZHWFCLFGLKORFQFZXZXTEXWGRJPZ99KAJYFDWZNMBKQXOLRCAPDZWTZIMSUDSNDTKJLKJ"
    "WFCTHZFYFW9EF9T9OGNFBNCRDDTRQUBIBSIWJNRAFXG9UDRGSXDQ9OKAREHQOCXSULYOA9IW"
    "JOYGWYOZGVQUDNBZXHZBCCBQ9PPKIKSWLNLPRSRRYLGCQIJKYNTAJBGPAOYWIUOIR9WOQYLS"
    "QYPWKUWBD9AUVZZT9KWUNQZYLOKTWRVJDVJSDBO9XYEGJIZWRMU9SRUVGMZUX9BXACUDYNXX"
    "RTYN9UVLJUIJGNAHVWSWRFHKIXTYINVHFHGXJVVJFLFTJR9LPZCJPHQOZQRXFJPYIHCVBXCI"
    "XZFPCC9RYLOYMBXDTRDEDWPZMZYIKGTXAQYJVEFDSF9QWROXAJS9ZPAWHLKIEKUPFKXOGLUY"
    "XCQNVVBYEJG9STYYRHKAOOID9UDPCMSBOVKWXCTSRSBKOZIIUDAABKXIBIDNTXZWLITYANTG"
    "VRYBEOZAOEWGPGLKGICMPADAEHHOCUSKXBKO9REVSI9FDFDCPMUGCLJVNHMHWHAIURTWDTSH"
    "MOPVVMGWLECCPXHAAQRCDCUWDVMBRLMQYTY9PLIFIUNXZUNY9UIVHBZKMNYOPRSIKBKWDDOY"
    "JQWCSPFBLODZVAPGWHJJKOBYETEUUPJDIFLWUCMYWEUSZLWANGHYSNUXJAPFZJADQWAZCOYX"
    "WJAQCYWFBRNXJRHMIUFEROW9Z9QJAPFDIRUUTD9RPZYFD9PRPU9YVGIQMHNEYVDLEIESZEO9"
    "QLOLNHSVNGNZFHODQXXX9K9NAUDG9UENCXFTS9FQXVXJYIVBL9OPHXTPCWKEDMXXJQLXHBNT"
    "NVWHGFNNXAEKGHSBGCQFFIIRKMSYRXBCDTUCJESVXJGZTHUJWGWDD9MDXBCXEPBMDZEVUGIX"
    "HVCGDFVOYY9QEJJYQALKJWFKMYSKZRXQNGI9MC9FLSIYER9BZGDXGZUAMBZFJLWNBKMWWOSU"
    "E9XGOUPDDSCJWN9PJD9LKUVVYHCRBBBABVKZJOXFGCRXXDEGLGYDXLFFPWFNCGCRPKGSEXQN"
    "ONXKJWDGTFZWWOSK9TKUTHGHBNLQADQ9QS9XLNRVUMSRFVYVSEQEGGTOWHUMZUEVQEROFMYL"
    "XYXU9GUJSQFSMMVHQS9SVIH9X9RNORYZOLIIA9RWAUFWDKQXRAHPALEW9LDXZFSRDCPYVSSX"
    "GOEPSVZCVWXDXVJKDWUBGQEUGNAUD9GNEQEVXXLTNVBIWJLLBCTFZWODFLIIDSNUPDJRHNPH"
    "9NBOKOVXCGEEZA9ZWKRNBL9XOOPF9OCP9VORMMVSIASCEAUVVJHBLWLHDHWVJDDTEBFIKHOE"
    "VIIDJXA9MTLUSZVPJPHLRASOAGNNPQYIAZVKTROQXISIALDESIHLNREAAPXCFU9AZTORQGYC"
    "FWVFHFQMAJPUSYVAEERWGQSKYFZJPWMOAEWXTUEGIDOSSCLBFLMBIZHYIQWSCNPZUTTSKCZX"
    "DSELK9KSBHTDSUID9LMBMYXQFAWBBRHFKMMBPTFKDNLQSZAMHMYASZXXKHXKPH9TOHVZUOXD"
    "CFHBDNAQEVOQQUGKEW9YQBZWMSVTJGNVUN9TUVYJ9XECFMVIIFTNSNBCUA9TOHPHAYDSAWJT"
    "JANNPZELFSWMVLBRUKJDT9B9VWCXBMUDNLVDEEWQRITLOTFLVOUDQGEEXK9CO9DCMNDY9VZU"
    "GMLVFKLUBNSQOABRDMIWVYGMENSBHUOMGIJ9MNKLST999999999999999999999999999999"
    "999999999999999999UMJOPYD99A99999999C99999999WUIHHDPDFBHIQLKEFLUOKIOVFOC"
    "PFPWBKUCCGA9YUUEPTLUXRLZHVKEOLJQWHBOLSCWKVXCOBSVJHY9YXDMTFSSWIPNAYXJPQNQ"
    "CZAIT9ADYOLDXZVBTEUWMVYOOODSCPKAWWHOFQTLZKRPURYBMCU9YHSIYQZ9999W9VELHQPP"
    "ERYSG9ZLLAHQKDLJQBKYYZOSRQOESEELED9CZHBLAMALTJJZAFWNMWGAAUFJMNQDGKVA9999"
    "999999999999999999999999999HDU9RGVJE999999999MMMMMMMMM999999999999999999"
    "999999999";

#define NUM_OF_TIMES 10

long diff_in_microsec(struct timeval start, struct timeval end) {
  long seconds = (end.tv_sec - start.tv_sec);
  return ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
}

void bench_pow(uint8_t const mwm) {
  struct timeval start, end;
  long run_time = 0;
  long min = 0, max = 0, sum = 0;
  tryte_t powed[NUM_TRYTES_SERIALIZED_TRANSACTION];

  char *tmp_nonce = NULL;
  char *tmp_hash = NULL;
  for (int i = 0; i < NUM_OF_TIMES; i++) {
    gettimeofday(&start, NULL);
    tmp_nonce = iota_pow_trytes((char *)TX_TRYTES, mwm);

    memcpy(powed, TX_TRYTES, NUM_TRYTES_SERIALIZED_TRANSACTION);
    memcpy(powed + NUM_TRYTES_SERIALIZED_TRANSACTION - NUM_TRYTES_NONCE, tmp_nonce, NUM_TRYTES_NONCE);
    tmp_hash = iota_digest((char *)powed);
    gettimeofday(&end, NULL);
    run_time = diff_in_microsec(start, end);
    max = (i == 0 || run_time > max) ? run_time : max;
    min = (i == 0 || run_time < min) ? run_time : min;
    sum += run_time;
    free(tmp_nonce);
    free(tmp_hash);
  }
  printf("MWM %d:\t%.3f\t%.3f\t%.3f\t%.3f\n", mwm, (min / 1000.0), (max / 1000.0), (sum / NUM_OF_TIMES) / 1000.0,
         sum / 1000.0);
}

void bench_flex_pow(uint8_t mwm) {
  struct timeval start, end;
  long run_time = 0;
  long min = 0, max = 0, sum = 0;
  flex_trit_t tx[FLEX_TRIT_SIZE_8019];

  flex_trit_t *tmp_nonce = NULL;
  flex_trit_t *tmp_hash = NULL;
  flex_trits_from_trytes(tx, NUM_TRITS_SERIALIZED_TRANSACTION, (tryte_t *)TX_TRYTES, NUM_TRYTES_SERIALIZED_TRANSACTION,
                         NUM_TRYTES_SERIALIZED_TRANSACTION);
  for (int i = 0; i < NUM_OF_TIMES; i++) {
    gettimeofday(&start, NULL);
    tmp_nonce = iota_pow_flex(tx, NUM_TRITS_SERIALIZED_TRANSACTION, mwm);
    flex_trits_insert_from_pos(tx, NUM_TRITS_SERIALIZED_TRANSACTION, tmp_nonce, NUM_TRITS_NONCE, 0,
                               NUM_TRITS_SERIALIZED_TRANSACTION - NUM_TRITS_NONCE, NUM_TRITS_NONCE);
    tmp_hash = iota_flex_digest(tx, NUM_TRITS_SERIALIZED_TRANSACTION);

    gettimeofday(&end, NULL);
    run_time = diff_in_microsec(start, end);
    max = (i == 0 || run_time > max) ? run_time : max;
    min = (i == 0 || run_time < min) ? run_time : min;
    sum += run_time;
    free(tmp_nonce);
    free(tmp_hash);
  }
  printf("Flex MWM %d:\t%.3f\t%.3f\t%.3f\t%.3f\n", mwm, (min / 1000.0), (max / 1000.0), (sum / NUM_OF_TIMES) / 1000.0,
         sum / 1000.0);
}

int main(void) {
  printf("Threads: %zu ", system_cpu_available());
  printf("Bench PoW on Tryes: %d times\n\tmin(ms)\tmax(ms)\tavg(ms)\ttotal(ms)\n", NUM_OF_TIMES);
  bench_pow(9);
  bench_pow(14);
  printf("Bench PoW on Flex Tryes: %d times\n\tmin(ms)\tmax(ms)\tavg(ms)\ttotal(ms)\n", NUM_OF_TIMES);
  bench_flex_pow(9);
  bench_flex_pow(14);

  return 0;
}
