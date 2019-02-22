#pragma once

#include "AUISkiaPreConfig.h"

#include <skia/core/SkColor.h>

// Alpha values
constexpr SkAlpha kAUIAlphaOpaque               = 0xFF;
constexpr SkAlpha kAUIAlphaTransparent          = 0x00;
constexpr SkAlpha kAUIAlpha_00                  = 0x00;
constexpr SkAlpha kAUIAlpha_10                  = 0x1A;
constexpr SkAlpha kAUIAlpha_20                  = 0x33;
constexpr SkAlpha kAUIAlpha_30                  = 0x4D;
constexpr SkAlpha kAUIAlpha_33                  = 0x54;
constexpr SkAlpha kAUIAlpha_40                  = 0x66;
constexpr SkAlpha kAUIAlpha_50                  = 0x7F;
constexpr SkAlpha kAUIAlpha_60                  = 0x99;
constexpr SkAlpha kAUIAlpha_66                  = 0xA8;
constexpr SkAlpha kAUIAlpha_70                  = 0xB2;
constexpr SkAlpha kAUIAlpha_80                  = 0xCC;
constexpr SkAlpha kAUIAlpha_90                  = 0xE6;
constexpr SkAlpha kAUIAlpha100                  = 0xFF;
// Mono color
constexpr SkColor kAUIColorTransparent          = 0x00000000;
constexpr SkColor kAUIColorBlack                = 0xFF000000;
constexpr SkColor kAUIColorDarkGray             = 0xFF444444;
constexpr SkColor kAUIColorGray                 = 0xFF888888;
constexpr SkColor kAUIColorLightGray            = 0xFFCCCCCC;
constexpr SkColor kAUIColorWhite                = 0xFFFFFFFF;
// RGB color
constexpr SkColor kAUIColorRed                  = 0xFFFF0000;
constexpr SkColor kAUIColorGreen                = 0xFF00FF00;
constexpr SkColor kAUIColorBlue                 = 0xFF0000FF;
// HTML color
constexpr SkColor kAUIColorYellow               = 0xFFFFFF00;
constexpr SkColor kAUIColorCyan                 = 0xFF00FFFF;
constexpr SkColor kAUIColorMagenta              = 0xFFFF00FF;
constexpr SkColor kAUIColorOrange               = 0xFFFF7F00;
constexpr SkColor kAUIColorSilver               = 0xFFC0C0C0;
constexpr SkColor kAUIColorSkyBlue              = 0xFF87CEEB;
constexpr SkColor kAUIColorPink                 = 0xFFFFC0CB;
constexpr SkColor kAUIColorAbsoluteZero         = 0xFF0048BA;
constexpr SkColor kAUIColorAcidGreen            = 0xFFB0BF1A;
constexpr SkColor kAUIColorAero                 = 0xFF7CB9E8;
constexpr SkColor kAUIColorAeroBlue             = 0xFFC9FFE5;
constexpr SkColor kAUIColorAliceBlue            = 0xFFF0F8FF;
constexpr SkColor kAUIColorAlienArmpit          = 0xFF84DE02;
constexpr SkColor kAUIColorAlloyOrange          = 0xFFC46210;
constexpr SkColor kAUIColorAlmond               = 0xFFEFDECD;
constexpr SkColor kAUIColorAmaranth             = 0xFFE52B50;
constexpr SkColor kAUIColorAmazon               = 0xFF3B7A57;
constexpr SkColor kAUIColorAmber                = 0xFFFFBF00;
constexpr SkColor kAUIColorAqua                 = 0xFF00FFFF;
constexpr SkColor kAUIColorArmyGreen            = 0xFF4B5320;
constexpr SkColor kAUIColorAshGrey              = 0xFFB2BEB5;
constexpr SkColor kAUIColorAtomicTangerine      = 0xFFFF9966;
constexpr SkColor kAUIColorAzure                = 0xFF007FFF;
constexpr SkColor kAUIColorAzureWeb             = 0xFFF0FFFF;
constexpr SkColor kAUIColorBabyBlue             = 0xFF89CFF0;
constexpr SkColor kAUIColorBabyPink             = 0xFFF4C2C2;
constexpr SkColor kAUIColorBabyPowder           = 0xFFFEFEFA;
constexpr SkColor kAUIColorBananaMania          = 0xFFFAE7B5;
constexpr SkColor kAUIColorBananaYellow         = 0xFFFFE135;
constexpr SkColor kAUIColorBarbiePink           = 0xFFE0218A;
constexpr SkColor kAUIColorBatteryChargedBlue   = 0xFF1DACD6;
constexpr SkColor kAUIColorBattleshipGrey       = 0xFF848482;
constexpr SkColor kAUIColorBeaver               = 0xFF9F8170;
constexpr SkColor kAUIColorBeige                = 0xFFF5F5DC;
constexpr SkColor kAUIColorBisque               = 0xFFFFE4C4;
constexpr SkColor kAUIColorBitterLemon          = 0xFFCAE00D;
constexpr SkColor kAUIColorBitterLime           = 0xFFBFFF00;
constexpr SkColor kAUIColorBlackBean            = 0xFF3D0C02;
constexpr SkColor kAUIColorBlackCoral           = 0xFF54626F;
constexpr SkColor kAUIColorBlackLeatherJacket   = 0xFF253529;
constexpr SkColor kAUIColorBlackOlive           = 0xFF3B3C36;
constexpr SkColor kAUIColorBlackShadows         = 0xFFBFAFB2;
constexpr SkColor kAUIColorBleuDeFrance         = 0xFF318CE7;
constexpr SkColor kAUIColorBlizzardBlue         = 0xFFACE5EE;
constexpr SkColor kAUIColorBlond                = 0xFFFAF0BE;
constexpr SkColor kAUIColorBlueGray             = 0xFF6699CC;
constexpr SkColor kAUIColorBlueGreen            = 0xFF0D98BA;
constexpr SkColor kAUIColorBlueberry            = 0xFF4F86F7;
constexpr SkColor kAUIColorBone                 = 0xFFE3DAC9;
constexpr SkColor kAUIColorBronze               = 0xFFCD7F32;
constexpr SkColor kAUIColorBronzeYellow         = 0xFF737000;
constexpr SkColor kAUIColorBrownWeb             = 0xFFA52A2A;
constexpr SkColor kAUIColorBrown                = 0xFF964B00;
constexpr SkColor kAUIColorCamel                = 0xFFC19A6B;
constexpr SkColor kAUIColorCanary               = 0xFFFFFF99;
constexpr SkColor kAUIColorCanaryYellow         = 0xFFFFEF00;
constexpr SkColor kAUIColorCarrotOrange         = 0xFFED9121;
constexpr SkColor kAUIColorChampagne            = 0xFFF7E7CE;
constexpr SkColor kAUIColorChampagnePink        = 0xFFF1DDCF;
constexpr SkColor kAUIColorCherry               = 0xFFDE3163;
constexpr SkColor kAUIColorCherryBlossomPink    = 0xFFFFB7C5;
constexpr SkColor kAUIColorChinaPink            = 0xFFDE6FA1;
constexpr SkColor kAUIColorChinaRose            = 0xFFA8516E;
constexpr SkColor kAUIColorChineseRed           = 0xFFAA381E;
constexpr SkColor kAUIColorChineseViolet        = 0xFF856088;
constexpr SkColor kAUIColorChocolate            = 0xFF7B3F00;
constexpr SkColor kAUIColorChocolateWeb         = 0xFFD2691E;
constexpr SkColor kAUIColorChromeYellow         = 0xFFFFA700;
constexpr SkColor kAUIColorCinnamon             = 0xFFD2691E;
constexpr SkColor kAUIColorCitrine              = 0xFFE4D00A;
constexpr SkColor kAUIColorCitron               = 0xFF9FA91F;
constexpr SkColor kAUIColorClaret               = 0xFF7F1734;
constexpr SkColor kAUIColorClassicRose          = 0xFFFBCCE7;
constexpr SkColor kAUIColorCobaltBlue           = 0xFF0047AB;
constexpr SkColor kAUIColorCocoaBrown           = 0xFFD2691E;
constexpr SkColor kAUIColorCoconut              = 0xFF965A3E;
constexpr SkColor kAUIColorCoffee               = 0xFF6F4E37;
constexpr SkColor kAUIColorColumbiaBlue         = 0xFFC4D8E2;
constexpr SkColor kAUIColorCopper               = 0xFFB87333;
constexpr SkColor kAUIColorCopperRed            = 0xFFCB6D51;
constexpr SkColor kAUIColorCoral                = 0xFFFF7F50;
constexpr SkColor kAUIColorCorn                 = 0xFFFBEC5D;
constexpr SkColor kAUIColorCornellRed           = 0xFFB31B1B;
constexpr SkColor kAUIColorCosmicCobalt         = 0xFF2E2D88;
constexpr SkColor kAUIColorCottonCandy          = 0xFFFFBCD9;
constexpr SkColor kAUIColorCream                = 0xFFFFFDD0;
constexpr SkColor kAUIColorCrimson              = 0xFFDC143C;
constexpr SkColor kAUIColorCultured             = 0xFFF5F5F5;
constexpr SkColor kAUIColorCyanAzure            = 0xFF4E82B4;
constexpr SkColor kAUIColorCyanProcess          = 0xFF00B7EB;
constexpr SkColor kAUIColorDarkBlue             = 0xFF00008B;
constexpr SkColor kAUIColorDarkBlueGray         = 0xFF666699;
constexpr SkColor kAUIColorDarkBrown            = 0xFF654321;
constexpr SkColor kAUIColorDarkCyan             = 0xFF008B8B;
constexpr SkColor kAUIColorDarkElectricBlue     = 0xFF836878;
constexpr SkColor kAUIColorDarkGrayX11          = 0xFFA9A9A9;
constexpr SkColor kAUIColorDarkGreen            = 0xFF013220;
constexpr SkColor kAUIColorDarkGreenX11         = 0xFF006400;
constexpr SkColor kAUIColorDarkGunmetal         = 0xFF1F262A;
constexpr SkColor kAUIColorDarkImperialBlue     = 0xFF00416A;
constexpr SkColor kAUIColorDarkJungleGreen      = 0xFF1A2421;
constexpr SkColor kAUIColorDarkLava             = 0xFF483C32;
constexpr SkColor kAUIColorDarkLavender         = 0xFF734F96;
constexpr SkColor kAUIColorDarkLiver            = 0xFF534B4F;
constexpr SkColor kAUIColorDarkMagenta          = 0xFF8B008B;
constexpr SkColor kAUIColorDarkOliveGreen       = 0xFF556B2F;
constexpr SkColor kAUIColorDarkOrange           = 0xFFFF8C00;
constexpr SkColor kAUIColorDarkOrchid           = 0xFF9932CC;
constexpr SkColor kAUIColorDarkPastelBlue       = 0xFF779ECB;
constexpr SkColor kAUIColorDarkPastelGreen      = 0xFF03C03C;
constexpr SkColor kAUIColorDarkPastelPurple     = 0xFF966FD6;
constexpr SkColor kAUIColorDarkPastelRed        = 0xFFC23B22;
constexpr SkColor kAUIColorDarkPink             = 0xFFE75480;
constexpr SkColor kAUIColorDarkPuce             = 0xFF4F3A3C;
constexpr SkColor kAUIColorDarkPurple           = 0xFF301934;
constexpr SkColor kAUIColorDarkRaspberry        = 0xFF872657;
constexpr SkColor kAUIColorDarkRed              = 0xFF8B0000;
constexpr SkColor kAUIColorDarkSalmon           = 0xFFE9967A;
constexpr SkColor kAUIColorDarkScarlet          = 0xFF560319;
constexpr SkColor kAUIColorDarkSeaGreen         = 0xFF8FBC8F;
constexpr SkColor kAUIColorDarkSienna           = 0xFF8FBC8F;
constexpr SkColor kAUIColorDarkSkyBlue          = 0xFF8CBED6;
constexpr SkColor kAUIColorDarkSlateBlue        = 0xFF483D8B;
constexpr SkColor kAUIColorDarkSpringGreen      = 0xFF177245;
constexpr SkColor kAUIColorDarkTan              = 0xFF918151;
constexpr SkColor kAUIColorDarkTangerine        = 0xFFFFA812;
constexpr SkColor kAUIColorDarkTurquoise        = 0xFF00CED1;
constexpr SkColor kAUIColorDarkVanilla          = 0xFFD1BEA8;
constexpr SkColor kAUIColorDarkViolet           = 0xFF9400D3;
constexpr SkColor kAUIColorDarkYellow           = 0xFF9B870C;
constexpr SkColor kAUIColorDebianRed            = 0xFFD70A53;
constexpr SkColor kAUIColorDeepCoffee           = 0xFF704241;
constexpr SkColor kAUIColorDeepGreen            = 0xFF056608;
constexpr SkColor kAUIColorDeepLemon            = 0xFFF5C71A;
constexpr SkColor kAUIColorDeepLilac            = 0xFF9955BB;
constexpr SkColor kAUIColorDeepMagenta          = 0xFFCC00CC;
constexpr SkColor kAUIColorDeepPeach            = 0xFFFFCBA4;
constexpr SkColor kAUIColorDeepPink             = 0xFFFF1493;
constexpr SkColor kAUIColorDeepRed              = 0xFF850101;
constexpr SkColor kAUIColorDeepRuby             = 0xFF843F5B;
constexpr SkColor kAUIColorDeepSkyBlue          = 0xFF00BFFF;
constexpr SkColor kAUIColorDeepViolet           = 0xFF330066;
constexpr SkColor kAUIColorDeer                 = 0xFFBA8759;
constexpr SkColor kAUIColorDenim                = 0xFF1560BD;
constexpr SkColor kAUIColorDenimBlue            = 0xFF2243B6;
constexpr SkColor kAUIColorDesert               = 0xFFC19A9B;
constexpr SkColor kAUIColorDesertSand           = 0xFFEDC9AF;
constexpr SkColor kAUIColorDiamond              = 0xFFB9F2FF;
constexpr SkColor kAUIColorDimGray              = 0xFF696969;
constexpr SkColor kAUIColorDirt                 = 0xFF9B7653;
constexpr SkColor kAUIColorDolphinGray          = 0xFF828E84;
constexpr SkColor kAUIColorDonkeyBrown          = 0xFF664C28;
constexpr SkColor kAUIColorDukeBlue             = 0xFF00009C;
constexpr SkColor kAUIColorDustStrom            = 0xFFE5CCC9;
constexpr SkColor kAUIColorEarthYellow          = 0xFFE1A95F;
constexpr SkColor kAUIColorEgyptianBlue         = 0xFF1034A6;
constexpr SkColor kAUIColorElectricBlue         = 0xFF7DF9FF;
constexpr SkColor kAUIColorEmerald              = 0xFF50C878;
constexpr SkColor kAUIColorEnglishGreen         = 0xFF1B4D3E;
constexpr SkColor kAUIColorEnglishLavender      = 0xFFB48395;
constexpr SkColor kAUIColorEnglishRed           = 0xFFAB4B52;
constexpr SkColor kAUIColorEnglishVermillion    = 0xFFCC474B;
constexpr SkColor kAUIColorEnglishViolet        = 0xFF563C5C;
constexpr SkColor kAUIColorEucalyptus           = 0xFF44D7A8;
constexpr SkColor kAUIColorFerrariRed           = 0xFFFF2800;
constexpr SkColor kAUIColorFlame                = 0xFFE25822;
constexpr SkColor kAUIColorFluorescentOrange    = 0xFFFFBF00;
constexpr SkColor kAUIColorFluorescentPink      = 0xFFFF1493;
constexpr SkColor kAUIColorFluorescentYellow    = 0xFFCCFF00;
constexpr SkColor kAUIColorForestGreen          = 0xFF014421;
constexpr SkColor kAUIColorForestGreenWeb       = 0xFF228B22;
constexpr SkColor kAUIColorFrenchBeige          = 0xFFA67B5B;
constexpr SkColor kAUIColorFrenchBistre         = 0xFF856D4D;
constexpr SkColor kAUIColorFrenchBlue           = 0xFF0072BB;
constexpr SkColor kAUIColorFrenchFuchsia        = 0xFFFD3F92;
constexpr SkColor kAUIColorFrenchLilac          = 0xFF86608E;
constexpr SkColor kAUIColorFrenchLime           = 0xFF9EFD38;
constexpr SkColor kAUIColorFrenchMauve          = 0xFFD473D4;
constexpr SkColor kAUIColorFrenchPink           = 0xFFFD6C9E;
constexpr SkColor kAUIColorFrenchPlum           = 0xFF811453;
constexpr SkColor kAUIColorFrenchRspberry       = 0xFFC72C48;
constexpr SkColor kAUIColorFrenchRose           = 0xFFF64A8A;
constexpr SkColor kAUIColorFrenchSkyBlue        = 0xFF77B5FE;
constexpr SkColor kAUIColorFrenchViolet         = 0xFF8806CE;
constexpr SkColor kAUIColorFrenchWine           = 0xFFAC1E44;
constexpr SkColor kAUIColorFreshAir             = 0xFFA6E7FF;
constexpr SkColor kAUIColorFrostbite            = 0xFFE936A7;
constexpr SkColor kAUIColorGhostWhite           = 0xFFF8F8FF;
constexpr SkColor kAUIColorGiantsOrgane         = 0xFFFE5A1D;
constexpr SkColor kAUIColorGinger               = 0xFFB06500;
constexpr SkColor kAUIColorGlaucous             = 0xFF6082B6;
constexpr SkColor kAUIColorGlossyGrape          = 0xFFAB92B3;
constexpr SkColor kAUIColorGold                 = 0xFFD4AF37;
constexpr SkColor kAUIColorGoldWeb              = 0xFFFFD700;
constexpr SkColor kAUIColorGoldenBrown          = 0xFF996515;
constexpr SkColor kAUIColorGoldenYellow         = 0xFFFFDF00;
constexpr SkColor kAUIColorGoldenrod            = 0xFFDAA520;
constexpr SkColor kAUIColorGrannySmithApple     = 0xFFA8E4A0;
constexpr SkColor kAUIColorGrape                = 0xFF6F2DA8;
constexpr SkColor kAUIColorGrayX11              = 0xFFBEBEBE;
constexpr SkColor kAUIColorGrayBlue             = 0xFF8C92AC;
constexpr SkColor kAUIColorGreenCSS             = 0xFF008000;
constexpr SkColor kAUIColorHotPink              = 0xFFFF69B4;
constexpr SkColor kAUIColorHotMagenta           = 0xFFFF1DCE;
constexpr SkColor kAUIColorIceberg              = 0xFF71A6D2;
constexpr SkColor kAUIColorImperial             = 0xFF602F6B;
constexpr SkColor kAUIColorImperialBlue         = 0xFF002395;
constexpr SkColor kAUIColorImperialPurple       = 0xFF66023C;
constexpr SkColor kAUIColorImperialRed          = 0xFFED2939;
constexpr SkColor kAUIColorIndiaGreen           = 0xFF138808;
constexpr SkColor kAUIColorIndianRed            = 0xFFCD5C5C;
constexpr SkColor kAUIColorIndianYellow         = 0xFFE3A857;
constexpr SkColor kAUIColorIndigo               = 0xFF4B0082;
constexpr SkColor kAUIColorInfraRed             = 0xFFFF496C;
constexpr SkColor kAUIColorIris                 = 0xFF5A4FCF;
constexpr SkColor kAUIColorIvory                = 0xFFFFFFF0;
constexpr SkColor kAUIColorJade                 = 0xFF00A86B;
constexpr SkColor kAUIColorJapaneseCarmine      = 0xFF9D2933;
constexpr SkColor kAUIColorJapaneseIndigo       = 0xFF264348;
constexpr SkColor kAUIColorJapaneseViolet       = 0xFF5B3256;
constexpr SkColor kAUIColorJasper               = 0xFFD73B3E;
constexpr SkColor kAUIColorJellyBean            = 0xFFDA615E;
constexpr SkColor kAUIColorJungleGreen          = 0xFF29AB87;
constexpr SkColor kAUIColorKiwi                 = 0xFF8EE53F;
constexpr SkColor kAUIColorKobe                 = 0xFF882D17;
constexpr SkColor kAUIColorKobi                 = 0xFFE79FC4;
constexpr SkColor kAUIColorLava                 = 0xFFCF1020;
constexpr SkColor kAUIColorLavender             = 0xFFB57EDC;
constexpr SkColor kAUIColorLavenderWeb          = 0xFFE6E6FA;
constexpr SkColor kAUIColorLavenderBlue         = 0xFFCCCCFF;
constexpr SkColor kAUIColorLavenderBlush        = 0xFFFFF0F5;
constexpr SkColor kAUIColorLavenderGray         = 0xFFC4C3D0;
constexpr SkColor kAUIColorLavenderIndigo       = 0xFF9457EB;
constexpr SkColor kAUIColorLavenderMagenta      = 0xFFEE82EE;
constexpr SkColor kAUIColorLavenderMist         = 0xFFE6E6FA;
constexpr SkColor kAUIColorLavenderPink         = 0xFFFBAED2;
constexpr SkColor kAUIColorLavenderPurple       = 0xFF967BB6;
constexpr SkColor kAUIColorLavenderRose         = 0xFFFBA0E3;
constexpr SkColor kAUIColorLemon                = 0xFFFFF700;
constexpr SkColor kAUIColorLemonChiffon         = 0xFFFFFACD;
constexpr SkColor kAUIColorLemonLime            = 0xFFE3FF00;
constexpr SkColor kAUIColorLemonYellow          = 0xFFFFF44F;
constexpr SkColor kAUIColorLiberty              = 0xFF545AA7;
constexpr SkColor kAUIColorLightBlue            = 0xFFADD8E6;
constexpr SkColor kAUIColorLightBrown           = 0xFFB5651D;
constexpr SkColor kAUIColorLightCobaltBlue      = 0xFF88ACE0;
constexpr SkColor kAUIColorLightCrimson         = 0xFFF56991;
constexpr SkColor kAUIColorLightCyan            = 0xFFE0FFFF;
constexpr SkColor kAUIColorLightDeepPink        = 0xFFFF5CCD;
constexpr SkColor kAUIColorLightGoldenrodYellow = 0xFFFAFAD2;
constexpr SkColor kAUIColorLightGreen           = 0xFF90EE90;
constexpr SkColor kAUIColorLightKhaki           = 0xFFF0E68C;
constexpr SkColor kAUIColorLightHotPink         = 0xFFFFB3DE;
constexpr SkColor kAUIColorLightMossGreen       = 0xFFADDFAD;
constexpr SkColor kAUIColorLightOrchid          = 0xFFE6A8D7;
constexpr SkColor kAUIColorLightPastelPurple    = 0xFFB19CD9;
constexpr SkColor kAUIColorLightPink            = 0xFFFFB6C1;
constexpr SkColor kAUIColorLightRedOchre        = 0xFFE97451;
constexpr SkColor kAUIColorLightSalmon          = 0xFFFFA07A;
constexpr SkColor kAUIColorLightSalmonPink      = 0xFFFF9999;
constexpr SkColor kAUIColorLightSeaGreen        = 0xFF20B2AA;
constexpr SkColor kAUIColorLightSkyBlue         = 0xFF87CEFA;
constexpr SkColor kAUIColorLightSlateGray       = 0xFF778899;
constexpr SkColor kAUIColorLightSteelBlue       = 0xFFB0C4DE;
constexpr SkColor kAUIColorLightYellow          = 0xFFFFFFE0;
constexpr SkColor kAUIColorLilac                = 0xFFC8A2C8;
constexpr SkColor kAUIColorLime                 = 0xFFBFFF00;
constexpr SkColor kAUIColorLimeGreen            = 0xFF32CD32;
constexpr SkColor kAUIColorLimerick             = 0xFF9DC209;
constexpr SkColor kAUIColorLion                 = 0xFFC19A6B;
constexpr SkColor kAUIColorLiver                = 0xFF674C47;
constexpr SkColor kAUIColorLiverOrgan           = 0xFF6C2E1F;
constexpr SkColor kAUIColorLumber               = 0xFFFFE4CD;
constexpr SkColor kAUIColorMantis               = 0xFF74C365;
constexpr SkColor kAUIColorMaroonCSS            = 0xFF800000;
constexpr SkColor kAUIColorMaroonX11            = 0xFFB03060;
constexpr SkColor kAUIColorMaximumBlue          = 0xFF47ABCC;
constexpr SkColor kAUIColorMaximumBlueGreen     = 0xFF30BFBF;
constexpr SkColor kAUIColorMaximumBluePurple    = 0xFFACACE6;
constexpr SkColor kAUIColorMaximumGreen         = 0xFF5E8C31;
constexpr SkColor kAUIColorMaximumGreenYellow   = 0xFFD9E650;
constexpr SkColor kAUIColorMaximumPurple        = 0xFF733380;
constexpr SkColor kAUIColorMaximumRed           = 0xFFD92121;
constexpr SkColor kAUIColorMaximumRedPurple     = 0xFFA63A79;
constexpr SkColor kAUIColorMaximumYellow        = 0xFFFAFA37;
constexpr SkColor kAUIColorMaximumYellowRed     = 0xFFF2BA49;
constexpr SkColor kAUIColorMint                 = 0xFF3EB489;
constexpr SkColor kAUIColorMintCream            = 0xFFF5FFFA;
constexpr SkColor kAUIColorMintGreen            = 0xFF98FF98;
constexpr SkColor kAUIColorMistyMoss            = 0xFFBBB477;
constexpr SkColor kAUIColorMistyRose            = 0xFFFFE4E1;
constexpr SkColor kAUIColorMoccasin             = 0xFFFAEBD7;
constexpr SkColor kAUIColorMustard              = 0xFFFFDB58;
constexpr SkColor kAUIColorNavy                 = 0xFF000080;
constexpr SkColor kAUIColorNavyPurple           = 0xFF9457EB;
constexpr SkColor kAUIColorNeonCarrot           = 0xFFFFA343;
constexpr SkColor kAUIColorNeonFuchsia          = 0xFFFE4164;
constexpr SkColor kAUIColorNeonGreen            = 0xFF39FF14;
constexpr SkColor kAUIColorNickel               = 0xFF727472;
constexpr SkColor kAUIColorOceanBlue            = 0xFF4F42B5;
constexpr SkColor kAUIColorOceanBoatBlue        = 0xFF0077BE;
constexpr SkColor kAUIColorOceanGreen           = 0xFF48BF91;
constexpr SkColor kAUIColorOchre                = 0xFFCC7722;
constexpr SkColor kAUIColorOlive                = 0xFF808000;
constexpr SkColor kAUIColorOnyx                 = 0xFF353839;
constexpr SkColor kAUIColorOrangeWeb            = 0xFFFFA500;
constexpr SkColor kAUIColorOrangeRed            = 0xFFFF4500;
constexpr SkColor kAUIColorOrangeSoda           = 0xFFFA5B3D;
constexpr SkColor kAUIColorOrangeYellow         = 0xFFF8D568;
constexpr SkColor kAUIColorOrchid               = 0xFFDA70D6;
constexpr SkColor kAUIColorOrchidPink           = 0xFFF2BDCD;
constexpr SkColor kAUIColorOxfordBlue           = 0xFF002147;
constexpr SkColor kAUIColorPacificBlue          = 0xFF1CA9C9;
constexpr SkColor kAUIColorPakistanGreen        = 0xFF006600;
constexpr SkColor kAUIColorPaleAqua             = 0xFFBCD4E6;
constexpr SkColor kAUIColorPaleBrown            = 0xFF987654;
constexpr SkColor kAUIColorPaleCopper           = 0xFFDA8A67;
constexpr SkColor kAUIColorPaleCyan             = 0xFF87D3F8;
constexpr SkColor kAUIColorPaleGold             = 0xFFE6BE8A;
constexpr SkColor kAUIColorPaleGoldenrod        = 0xFFEEE8AA;
constexpr SkColor kAUIColorPaleGreen            = 0xFF98FB98;
constexpr SkColor kAUIColorPaleLavender         = 0xFFDCD0FF;
constexpr SkColor kAUIColorPaleMagenta          = 0xFFF984E5;
constexpr SkColor kAUIColorPaleMagentaPink      = 0xFFFF99CC;
constexpr SkColor kAUIColorPalePink             = 0xFFFAFADD;
constexpr SkColor kAUIColorPalePlum             = 0xFFDDA0DD;
constexpr SkColor kAUIColorPaleSilver           = 0xFFC9C0BB;
constexpr SkColor kAUIColorPaleTurquoise        = 0xFFAFEEEE;
constexpr SkColor kAUIColorPaleViolet           = 0xFFCC99FF;
constexpr SkColor kAUIColorPaleVioletRed        = 0xFFDB7093;
constexpr SkColor kAUIColorPalmLeaf             = 0xFF6F9940;
constexpr SkColor kAUIColorParisGreen           = 0xFF50C878;
constexpr SkColor kAUIColorPastelBlue           = 0xFFAEC6CF;
constexpr SkColor kAUIColorPastelBrown          = 0xFF836953;
constexpr SkColor kAUIColorPastelGray           = 0xFFCFCFC4;
constexpr SkColor kAUIColorPastelGreen          = 0xFF77DD77;
constexpr SkColor kAUIColorPastelMagenta        = 0xFFF49AC2;
constexpr SkColor kAUIColorPastelOrange         = 0xFFFFB347;
constexpr SkColor kAUIColorPastelPink           = 0xFFDEA5A4;
constexpr SkColor kAUIColorPastelPurple         = 0xFFB39EB5;
constexpr SkColor kAUIColorPastelRed            = 0xFFFF6961;
constexpr SkColor kAUIColorPastelViolet         = 0xFFCB99C9;
constexpr SkColor kAUIColorPastelYellow         = 0xFFFDFD96;
constexpr SkColor kAUIColorPeach                = 0xFFFFE5B4;
constexpr SkColor kAUIColorPeachOragne          = 0xFFFFCC99;
constexpr SkColor kAUIColorPeachYellow          = 0xFFFADFAD;
constexpr SkColor kAUIColorPear                 = 0xFFD1E231;
constexpr SkColor kAUIColorPearl                = 0xFFEAE0C8;
constexpr SkColor kAUIColorPearlAqua            = 0xFF88D8C0;
constexpr SkColor kAUIColorPearlyPurple         = 0xFFB768A2;
constexpr SkColor kAUIColorPineGreen            = 0xFF01796F;
constexpr SkColor kAUIColorPineapple            = 0xFF563C5C;
constexpr SkColor kAUIColorPinkPearl            = 0xFFE7ACCF;
constexpr SkColor kAUIColorPlantinum            = 0xFFE5E4E2;
constexpr SkColor kAUIColorPurple               = 0xFFA020F0;
constexpr SkColor kAUIColorPurpleHTML           = 0xFF800080;
constexpr SkColor kAUIColorQuartz               = 0xFF51484F;
constexpr SkColor kAUIColorQuickSilver          = 0xFFA6A6A6;
constexpr SkColor kAUIColorRaspberry            = 0xFFE30B5D;
constexpr SkColor kAUIColorRaspberryPink        = 0xFFE25098;
constexpr SkColor kAUIColorRaspberryRose        = 0xFFB3446C;
constexpr SkColor kAUIColorRedBrown             = 0xFFA52A2A;
constexpr SkColor kAUIColorRedOrange            = 0xFFFF5349;
constexpr SkColor kAUIColorRedPurple            = 0xFFE40078;
constexpr SkColor kAUIColorRedwood              = 0xFFA45A52;
constexpr SkColor kAUIColorRose                 = 0xFFFF007F;
constexpr SkColor kAUIColorRoseGold             = 0xFFB76E79;
constexpr SkColor kAUIColorRoseRed              = 0xFFC21E56;
constexpr SkColor kAUIColorRuby                 = 0xFFE0115F;
constexpr SkColor kAUIColorRubyRed              = 0xFF9B111E;
constexpr SkColor kAUIColorRust                 = 0xFFB7410E;
constexpr SkColor kAUIColorSand                 = 0xFFC2B280;
constexpr SkColor kAUIColorSandDune             = 0xFF967117;
constexpr SkColor kAUIColorSandstrom            = 0xFFECD540;
constexpr SkColor kAUIColorSandyBrown           = 0xFFF4A460;
constexpr SkColor kAUIColorSandyTan             = 0xFFFDD9B5;
constexpr SkColor kAUIColorSapphire             = 0xFF0F52BA;
constexpr SkColor kAUIColorSapphireBlue         = 0xFF0067A5;
constexpr SkColor kAUIColorScarlet              = 0xFFFF2400;
constexpr SkColor kAUIColorSchoolBusYellow      = 0xFFFFD800;
constexpr SkColor kAUIColorSeaBlue              = 0xFF006994;
constexpr SkColor kAUIColorSeaFoamGreen         = 0xFF9FE2BF;
constexpr SkColor kAUIColorSeaGreen             = 0xFF2E8B57;
constexpr SkColor kAUIColorSeaSerpent           = 0xFF4BC7CF;
constexpr SkColor kAUIColorSeashell             = 0xFFFFF5EE;
constexpr SkColor kAUIColorSepia                = 0xFF704214;
constexpr SkColor kAUIColorShadow               = 0xFF8A795D;
constexpr SkColor kAUIColorShadowBlue           = 0xFF778BA5;
constexpr SkColor kAUIColorShampoo              = 0xFFFFCFF1;
constexpr SkColor kAUIColorSilverPink           = 0xFFC4AEAD;
constexpr SkColor kAUIColorSkyMagenta           = 0xFFCF71AF;
constexpr SkColor kAUIColorSlateBlue            = 0xFF6A5ACD;
constexpr SkColor kAUIColorSlateGray            = 0xFF708090;
constexpr SkColor kAUIColorSmoke                = 0xFF738276;
constexpr SkColor kAUIColorSnow                 = 0xFFFFFAFA;
constexpr SkColor kAUIColorSoap                 = 0xFFCEC8EF;
constexpr SkColor kAUIColorSteelBlue            = 0xFF4682B4;
constexpr SkColor kAUIColorSteelPink            = 0xFFCC33CC;
constexpr SkColor kAUIColorSteelTeal            = 0xFF5F8A8B;
constexpr SkColor kAUIColorStrawberry           = 0xFFFC5A8D;
constexpr SkColor kAUIColorSunny                = 0xFFF2F27A;
constexpr SkColor kAUIColorSunglow              = 0xFFFFCC33;
constexpr SkColor kAUIColorSunray               = 0xFFE3AB57;
constexpr SkColor kAUIColorSunset               = 0xFFFAD6A5;
constexpr SkColor kAUIColorTan                  = 0xFFD2B48C;
constexpr SkColor kAUIColorTangelo              = 0xFFF94D00;
constexpr SkColor kAUIColorTangerine            = 0xFFF28500;
constexpr SkColor kAUIColorTangerineYellow      = 0xFFFFCC00;
constexpr SkColor kAUIColorTangoPink            = 0xFFE4717A;
constexpr SkColor kAUIColorTaupe                = 0xFF483C32;
constexpr SkColor kAUIColorTaupeGray            = 0xFF8B8589;
constexpr SkColor kAUIColorTeaGreen             = 0xFFD0F0C0;
constexpr SkColor kAUIColorTeaRose              = 0xFFF4C2C2;
constexpr SkColor kAUIColorThistle              = 0xFFD8BFD8;
constexpr SkColor kAUIColorTiffanyBlue          = 0xFF0ABAB5;
constexpr SkColor kAUIColorTitaniumYellow       = 0xFFEEE600;
constexpr SkColor kAUIColorTomato               = 0xFFFF6347;
constexpr SkColor kAUIColorTopaz                = 0xFFFFC87C;
constexpr SkColor kAUIColorTrueBlue             = 0xFF0073CF;
constexpr SkColor kAUIColorTulip                = 0xFFFF878D;
constexpr SkColor kAUIColorTurquoise            = 0xFF40E0D0;
constexpr SkColor kAUIColorTurquoiseBlue        = 0xFF00FFEF;
constexpr SkColor kAUIColorTurquoiseGreen       = 0xFFA0D6B4;
constexpr SkColor kAUIColorTurquoiseSurf        = 0xFF00C5CD;
constexpr SkColor kAUIColorTuscan               = 0xFFFAD6A5;
constexpr SkColor kAUIColorTuscany              = 0xFFC09999;
constexpr SkColor kAUIColorUmber                = 0xFF635147;
constexpr SkColor kAUIColorVanilla              = 0xFFF3E5AB;
constexpr SkColor kAUIColorVanillaIce           = 0xFFF38FA9;
constexpr SkColor kAUIColorVeronica             = 0xFFA020F0;
constexpr SkColor kAUIColorViolet               = 0xFF8F00FF;
constexpr SkColor kAUIColorVioletWeb            = 0xFFEE82EE;
constexpr SkColor kAUIColorVistaBlue            = 0xFF7C9ED9;
constexpr SkColor kAUIColorWheat                = 0xFFF5DEB3;
constexpr SkColor kAUIColorWhiteSmoke           = 0xFFF5F5F5;
constexpr SkColor kAUIColorWine                 = 0xFF722F37;