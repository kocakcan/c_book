#include <limits.h>
#include <stdio.h>
#define BOSS_COUNT 24
#define PRINTB(b, n, l)                                                        \
  printf(                                                                      \
      "Name: %-*s | Location: %-*s | HP: %-4d | Souls: %-5d | Weakness: %s\n"  \
      "Physical: %d | Fire: %d | Magic: %d | Lightning: %d\n",                 \
      (int)(n), (b)->name, (int)(l), (b)->location, (b)->hp, (b)->souls,       \
      weak_to_string((b)->weakness), (b)->pres, (b)->fres, (b)->mres,          \
      (b)->lres)

enum WEAKNESS { PHYSICAL, MAGIC, FIRE, LIGHTNING };

struct Boss {
  char *name;
  char *location;
  int hp;
  int pres; /* physical resistance */
  int fres; /* fire resistance */
  int mres; /* magic resistance */
  int lres; /* lightning resistance */
  enum WEAKNESS weakness;
  int souls;
  char *reward[7];
};

int strcmp_(const char *, const char *);
size_t strlen_(const char *s);
size_t get_longest_name(struct Boss *);
size_t get_longest_location(struct Boss *);
const char *weak_to_string(enum WEAKNESS);
struct Boss *find_by_name(struct Boss *, const char *);
int most_common_weakness(struct Boss *);
int get_max_weakness_count(int *);

static struct Boss asylum_demon = {"Asylum Demon",
                                   "Undead Asylum",
                                   800,
                                   83,
                                   66,
                                   62,
                                   54,
                                   LIGHTNING,
                                   2000,
                                   {"Big Pilgrim Key", "Humanity"}};
static struct Boss bell_gargoyles = {"Bell Gargoyles",
                                     "Undead Parish",
                                     1479,
                                     133,
                                     98,
                                     103,
                                     104,
                                     FIRE,
                                     10000,
                                     {"Gargoyle Helm", "Gargoyle Halberd",
                                      "Gargoyle's Shield",
                                      "Gargoyle Tail Axe"}};
static struct Boss capra_demon = {
    "Capra Demon",
    "Lower Undead Burg",
    1176,
    159,
    127,
    119,
    106,
    LIGHTNING,
    6000,
    {"Key to the Depths", "Humanity", "Homeward Bone", "Demon Great Machete"}};
static struct Boss super_ornstein = {
    "Super Ornstein",
    "Anor Londo",
    2981,
    339,
    221,
    256,
    1657,
    MAGIC,
    50000,
    {"Soul of Ornstein", "Leo Ring", "Humanity"}};
static struct Boss super_smough = {"Super Smough",
                                   "Anor Londo",
                                   4094,
                                   180,
                                   125,
                                   153,
                                   359,
                                   FIRE,
                                   50000,
                                   {"Soul of Smough", "Humanity"}};
static struct Boss quelagg = {"Chaos Witch Quelagg",
                              "Quelagg's Domain",
                              3139,
                              255,
                              INT_MAX,
                              229,
                              205,
                              LIGHTNING,
                              20000,
                              {"Soul of Quelagg", "Twin Humanities"}};
static struct Boss priscilla = {"Crossbreed Priscilla",
                                "Painted World of Ariamis",
                                2300,
                                324,
                                195,
                                291,
                                195,
                                LIGHTNING,
                                30000,
                                {"Soul of Priscilla", "Priscilla's Dagger"}};
static struct Boss gwyndolin = {"Dark Sun Gwyndolin",
                                "Darkmoon Tomb",
                                2011,
                                251,
                                155,
                                251,
                                251,
                                FIRE,
                                40000,
                                {"Soul of Gwyndolin"}};
static struct Boss gaping_dragon = {"Gaping Dragon",
                                    "Depths",
                                    4660,
                                    167,
                                    108,
                                    117,
                                    84,
                                    LIGHTNING,
                                    25000,
                                    {"Blighttown Key", "Twin Humanities",
                                     "Homeward Bone", "Dragon King Greataxe"}};
static struct Boss iron_golem = {
    "Iron Golem", "Sen's Fortress",
    2880,         408,
    305,          326,
    245,          LIGHTNING,
    40000,        {"Core of an Iron Golem", "Humanity"}};
static struct Boss pinwheel = {"Pinwheel",
                               "The Catacombs",
                               1326,
                               151,
                               121,
                               128,
                               99,
                               LIGHTNING,
                               15000,
                               {"Mask of the Child", "Mask of the Mother",
                                "Mask of the Father", "Rite of Kindling",
                                "Humanity", "Homeward Bone"}};
static struct Boss stray_demon = {
    "Stray Demon", "Undead Asylum",
    5250,          258,
    195,           207,
    168,           LIGHTNING,
    20000,         {"Titanite Slab", "Humanity", "Homeward Bone"}};
static struct Boss taurus_demon = {
    "Taurus Demon",
    "Undead Burg",
    1215,
    103,
    88,
    77,
    67,
    LIGHTNING,
    3000,
    {"Humanity", "Homeward Bone", "Demon's Greataxe"}};
static struct Boss sif = {
    "Sif, the Great Grey Wolf",
    "Darkroot Garden",
    3432,
    260,
    182,
    195,
    195,
    FIRE,
    40000,
    {"Soul of Sif", "Covenant of Artorias", "Humanity", "Homeward Bone"}};
static struct Boss moonlight_butterfly = {
    "Moonlight Butterfly",
    "Darkroot Garden",
    1506,
    184,
    110,
    230,
    148,
    FIRE,
    10000,
    {"Soul of the Moonlight Butterfly", "Humanity"}};
static struct Boss four_kings = {
    "Four Kings", "The Abyss",
    9504,         299,
    192,          205,
    177,          LIGHTNING,
    60000,        {"Bequeathed Lord Soul Shard", "Humanity (x4)"}};
static struct Boss ceaseless = {"Ceaseless Discharge",
                                "Demon Ruins",
                                4200,
                                315,
                                INT_MAX,
                                220,
                                252,
                                MAGIC,
                                20000,
                                {"Humanity", "Homeward Bone"}};
static struct Boss firesage = {"Demon Firesage",
                               "Demon Ruins",
                               5448,
                               255,
                               203,
                               192,
                               166,
                               LIGHTNING,
                               20000,
                               {"Demon's Catalyst"}};
static struct Boss sanctuary_guardian = {
    "Sanctuary Guardian",
    "Sanctuary Garden",
    2560,
    300,
    480,
    768,
    1056,
    FIRE,
    30000,
    {"Guardian Soul", "Guardian Tail (tail cut)", "Humanity"}};
static struct Boss seath = {"Seath the Scaleless",
                            "The Duke's Archives",
                            5525,
                            345,
                            207,
                            690,
                            207,
                            LIGHTNING,
                            60000,
                            {"Bequeathed Lord Soul Shard",
                             "Moonlight Greatsword (tail cut)", "Humanity"}};
static struct Boss nito = {"Gravelord Nito",
                           "Tomb of the Giants",
                           4317,
                           317,
                           221,
                           238,
                           317,
                           FIRE,
                           60000,
                           {"Lord Soul (Gravelord Nito)", "Humanity"}};
static struct Boss centipede_demon = {"Centipede Demon",
                                      "Demon Ruins",
                                      3432,
                                      269,
                                      INT_MAX,
                                      174,
                                      215,
                                      MAGIC,
                                      40000,
                                      {"Orange Charred Ring"}};
static struct Boss bed_of_chaos = {
    "The Bed of Chaos",
    "Lost Izalith",
    1,
    0,
    0,
    0,
    0,
    PHYSICAL,
    60000,
    {"Lord Soul (The Bed of Chaos)", "Humanity"}};
static struct Boss artorias = {"Knight Artorias",
                               "Royal Wood",
                               3750,
                               429,
                               636,
                               687,
                               591,
                               LIGHTNING,
                               50000,
                               {"Soul of Artorias", "Humanity"}};
