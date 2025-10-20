#include <limits.h>
#define PRINTB(b)                                                              \
  printf("Name: %s | Location: %s | HP: %d | Souls: %d | Weakness: %s\n"       \
         "Physical: %d | Fire: %d | Magic: %d | Lightning: %d\n",              \
         (b)->name, (b)->location, (b)->hp, (b)->souls,                        \
         weak_to_string((b)->weakness), (b)->pres, (b)->fres, (b)->mres,       \
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
