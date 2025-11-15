#include <limits.h>
#include <stdio.h>

#define PRINTB(b, n, l)                                                        \
  printf(                                                                      \
      "Name: %-*s | Location: %-*s | HP: %-5d | Souls: %-5d | Weakness: %s\n"  \
      "Physical: %d | Fire: %d | Magic: %d | Lightning: %d\n",                 \
      (int)(n), (b)->name, (int)(l), (b)->location, (b)->hp, (b)->souls,       \
      weak_to_string((b)->weakness), (b)->pres, (b)->fres, (b)->mres,          \
      (b)->lres)

#define BOSS_COUNT 44
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
enum WEAKNESS most_common_weakness(struct Boss *, int *);

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
static struct Boss manus = {"Manus, Father of the Abyss",
                            "Chasm of the Abyss",
                            6665,
                            324,
                            624,
                            768,
                            720,
                            FIRE,
                            60000,
                            {"Soul of Manus", "Humanity (x10)"}};
static struct Boss kalameet = {
    "Black Dragon Kalameet",
    "Royal Wood",
    5400,
    468,
    900,
    900,
    762,
    LIGHTNING,
    60000,
    {"Calamity Ring", "Obsidian Greatsword (tail cut)"}};
static struct Boss gwyn = {"Gwyn, Lord of Cinder",
                           "Kiln of the First Flame",
                           4185,
                           354,
                           249,
                           267,
                           1170,
                           FIRE,
                           70000,
                           {"Soul of Gywn, Lord of Cinder"}};
static struct Boss gundyr = {
    "Iudex Gundyr", "Cemetary of Ash", 1037, 18, 2, 5, -14, LIGHTNING,
    3000,           {"Coiled Sword"}};
static struct Boss vordt = {"Vordt of the Boreal Valley",
                            "High Wall of Lothric",
                            1328,
                            38,
                            18,
                            24,
                            15,
                            LIGHTNING,
                            3000,
                            {"Soul of Boreal Valley Vordt"}};
static struct Boss greatwood = {
    "Curse-Rotted Greatwood",
    "Undead Settlement",
    5405,
    44,
    -110,
    -14,
    -20,
    FIRE,
    7000,
    {"Transposing Kiln", "Soul of the Rotted Greatsword"}};
static struct Boss sage = {
    "Crystal Sage", "Road of Sacrifices",      2723, -22, 0, 40, 2, PHYSICAL,
    8000,           {"Soul of a Crystal Sage"}};
static struct Boss deacons = {
    "Deacons of the Deep",
    "Cathedral of the Deep",
    4099,
    -21,
    0,
    46,
    -2,
    LIGHTNING,
    13000,
    {"Small Doll", "Soul of the Deacons of the Deep"}};
static struct Boss abyss_watchers = {
    "Abyss Watchers",
    "Farron Keep",
    1548,
    18,
    8,
    10,
    -12,
    LIGHTNING,
    18000,
    {"Cinder of a Lord (Abyss Watchers)", "Soul of the Blood of the Wolf"}};
static struct Boss wolnir = {"High Lord Wolnir",
                             "Catacombs of Carthus",
                             15041,
                             36,
                             28,
                             24,
                             40,
                             PHYSICAL,
                             22000,
                             {"Soul of High Lord Wolnir"}};
static struct Boss odk = {"Old Demon King",
                          "Smouldering Lake",
                          5301,
                          0,
                          78,
                          5,
                          4,
                          PHYSICAL,
                          25000,
                          {"Soul of the Old Demon King"}};
static struct Boss pontiff = {"Pontiff Sulyvahn",
                              "Irithyll of the Boreal Valley",
                              5106,
                              0,
                              8,
                              12,
                              5,
                              PHYSICAL,
                              28000,
                              {"Soul of Pontiff Sulyvahn"}};
static struct Boss aldrich = {"Aldrich, Devourer of Gods",
                              "Anor Londo",
                              4727,
                              31,
                              22,
                              76,
                              30,
                              FIRE,
                              50000,
                              {"Soul of Aldrich"}};
static struct Boss yhorm = {
    "Yhorm the Giant",
    "Profaned Capital",
    27822,
    -33,
    100,
    -52,
    -79,
    LIGHTNING,
    36000,
    {"Cinder of a Lord (Yhorm the Giant)", "Soul of Yhorm the Giant"}};
static struct Boss dancer = {"Dancer of the Boreal Valley",
                             "High Wall of Lothric",
                             5111,
                             20,
                             18,
                             19,
                             17,
                             LIGHTNING,
                             60000,
                             {"Soul of the Dancer"}};
static struct Boss oceiros = {"Oceiros, the Consumed King",
                              "Consumed King's Garden",
                              8087,
                              20,
                              20,
                              40,
                              -40,
                              LIGHTNING,
                              58000,
                              {"Soul of Consumed Oceiros"}};
static struct Boss champ_gundyr = {"Champion Gundyr",
                                   "Untended Graves",
                                   4956,
                                   21,
                                   10,
                                   12,
                                   -12,
                                   LIGHTNING,
                                   60000,
                                   {"Soul of Champion Gundyr"}};
static struct Boss wyvern = {"Ancient Wyvern",
                             "Archdragon Peak",
                             7873,
                             66,
                             80,
                             54,
                             5,
                             LIGHTNING,
                             70000,
                             {"Dragon Head Stone"}};
static struct Boss nameless_king = {"The Nameless King",
                                    "Archdragon Peak",
                                    4577,
                                    -27,
                                    15,
                                    17,
                                    -70,
                                    LIGHTNING,
                                    80000,
                                    {"Soul of the Nameless King"}};
static struct Boss dragonslayer_armour = {"Dragonslayer Armour",
                                          "Lothric Castle",
                                          4581,
                                          35,
                                          20,
                                          24,
                                          72,
                                          FIRE,
                                          64000,
                                          {"Soul of Dragonslayer Armour"}};
