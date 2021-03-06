/*
 * Программный интерфейс управления целевым процессором
 * через адаптер JTAG.
 * Автор: С.Вакуленко.
 *
 * Этот файл распространяется в надежде, что он окажется полезным, но
 * БЕЗ КАКИХ БЫ ТО НИ БЫЛО ГАРАНТИЙНЫХ ОБЯЗАТЕЛЬСТВ; в том числе без косвенных
 * гарантийных обязательств, связанных с ПОТРЕБИТЕЛЬСКИМИ СВОЙСТВАМИ и
 * ПРИГОДНОСТЬЮ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ.
 *
 * Вы вправе распространять и/или изменять этот файл в соответствии
 * с условиями Генеральной Общественной Лицензии GNU (GPL) в том виде,
 * как она была опубликована Фондом Свободного ПО; либо версии 2 Лицензии
 * либо (по вашему желанию) любой более поздней версии. Подробности
 * смотрите в прилагаемом файле 'COPYING.txt'.
 */

#define NFLASH      16  /* Max flash regions. */

typedef struct _target_t target_t;

target_t *target_open (int need_reset, int disable_block);
void target_close (target_t *mc);

unsigned target_idcode (target_t *mc);
const char *target_cpu_name (target_t *mc);

unsigned target_flash_width (target_t *mc);
unsigned target_flash_bytes (target_t *mc);
void target_flash_configure (target_t *mc, unsigned first, unsigned last);
int target_flash_detect (target_t *mc, unsigned base,
	unsigned *mf, unsigned *dev, char *mfname, char *devname,
	unsigned *bytes, unsigned *width);
unsigned target_flash_next (target_t *mc, unsigned prev, unsigned *last);

int target_erase (target_t *mc, unsigned addr);
int target_erase_sector (target_t *mc, unsigned addr);
int target_erase_area (target_t *mc, unsigned addr, unsigned len);
void target_program_block (target_t *mc, unsigned addr,
	unsigned nwords, unsigned *data);
int target_flash_rewrite (target_t *mc, unsigned addr, unsigned bad, unsigned expected);

void target_read_start (target_t *t);
unsigned target_read_next (target_t *t, unsigned addr);
unsigned target_read_word (target_t *mc, unsigned addr);
void target_read_block (target_t *mc, unsigned addr,
	unsigned nwords, unsigned *data);

void target_write_word (target_t *mc, unsigned addr, unsigned word);
void target_write_next (target_t *mc, unsigned addr, unsigned word);
void target_write_block (target_t *mc, unsigned addr,
	unsigned nwords, unsigned *data);
void target_write_nwords (target_t *t, unsigned nwords, ...);
void target_write_byte (target_t *t, unsigned addr, unsigned data);
void target_write_2bytes (target_t *t, unsigned addr1, unsigned data1,
	unsigned addr2, unsigned data2);

void target_stop (target_t *t);
void target_step (target_t *t);
void target_resume (target_t *t);
void target_run (target_t *t, unsigned addr);
void target_restart (target_t *t);
int target_is_stopped (target_t *t, int *is_aborted);

unsigned target_read_register (target_t *t, unsigned regno);
void target_write_register (target_t *t, unsigned regno, unsigned val);

void target_add_break (target_t *t, unsigned addr, int type);
void target_remove_break (target_t *t, unsigned addr);

unsigned target_flash_address (target_t *mc, unsigned flash_num);
void target_set_cscon3 (target_t *t, unsigned value);
