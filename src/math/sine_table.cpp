#include <mathhelp.h>

namespace Lite {
namespace Utility {
namespace Math {

const double sine_table[SINE_TABLE_SIZE] = {double(0.0),
                                            double(0.024541228522912288),
                                            double(0.049067674327418015),
                                            double(0.073564563599667426),
                                            double(0.098017140329560604),
                                            double(0.1224106751992162),
                                            double(0.14673047445536175),
                                            double(0.17096188876030122),
                                            double(0.19509032201612825),
                                            double(0.2191012401568698),
                                            double(0.24298017990326387),
                                            double(0.26671275747489837),
                                            double(0.29028467725446233),
                                            double(0.31368174039889152),
                                            double(0.33688985339222005),
                                            double(0.35989503653498811),
                                            double(0.38268343236508978),
                                            double(0.40524131400498986),
                                            double(0.42755509343028208),
                                            double(0.44961132965460654),
                                            double(0.47139673682599764),
                                            double(0.49289819222978404),
                                            double(0.51410274419322166),
                                            double(0.53499761988709715),
                                            double(0.55557023301960218),
                                            double(0.57580819141784534),
                                            double(0.59569930449243336),
                                            double(0.61523159058062682),
                                            double(0.63439328416364549),
                                            double(0.65317284295377676),
                                            double(0.67155895484701833),
                                            double(0.68954054473706683),
                                            double(0.70710678118654746),
                                            double(0.72424708295146689),
                                            double(0.74095112535495911),
                                            double(0.75720884650648446),
                                            double(0.77301045336273699),
                                            double(0.78834642762660623),
                                            double(0.80320753148064483),
                                            double(0.81758481315158371),
                                            double(0.83146961230254524),
                                            double(0.84485356524970701),
                                            double(0.85772861000027212),
                                            double(0.87008699110871135),
                                            double(0.88192126434835494),
                                            double(0.89322430119551532),
                                            double(0.90398929312344334),
                                            double(0.91420975570353069),
                                            double(0.92387953251128674),
                                            double(0.93299279883473885),
                                            double(0.94154406518302081),
                                            double(0.94952818059303667),
                                            double(0.95694033573220894),
                                            double(0.96377606579543984),
                                            double(0.97003125319454397),
                                            double(0.97570213003852857),
                                            double(0.98078528040323043),
                                            double(0.98527764238894122),
                                            double(0.98917650996478101),
                                            double(0.99247953459870997),
                                            double(0.99518472667219682),
                                            double(0.99729045667869021),
                                            double(0.99879545620517241),
                                            double(0.99969881869620425),
                                            double(1.0),
                                            double(0.99969881869620425),
                                            double(0.99879545620517241),
                                            double(0.99729045667869021),
                                            double(0.99518472667219693),
                                            double(0.99247953459870997),
                                            double(0.98917650996478101),
                                            double(0.98527764238894122),
                                            double(0.98078528040323043),
                                            double(0.97570213003852857),
                                            double(0.97003125319454397),
                                            double(0.96377606579543984),
                                            double(0.95694033573220894),
                                            double(0.94952818059303667),
                                            double(0.94154406518302081),
                                            double(0.93299279883473885),
                                            double(0.92387953251128674),
                                            double(0.91420975570353069),
                                            double(0.90398929312344345),
                                            double(0.89322430119551521),
                                            double(0.88192126434835505),
                                            double(0.87008699110871146),
                                            double(0.85772861000027212),
                                            double(0.84485356524970723),
                                            double(0.83146961230254546),
                                            double(0.81758481315158371),
                                            double(0.80320753148064494),
                                            double(0.78834642762660634),
                                            double(0.7730104533627371),
                                            double(0.75720884650648468),
                                            double(0.74095112535495899),
                                            double(0.72424708295146689),
                                            double(0.70710678118654757),
                                            double(0.68954054473706705),
                                            double(0.67155895484701855),
                                            double(0.65317284295377664),
                                            double(0.63439328416364549),
                                            double(0.61523159058062693),
                                            double(0.59569930449243347),
                                            double(0.57580819141784545),
                                            double(0.55557023301960218),
                                            double(0.53499761988709715),
                                            double(0.51410274419322177),
                                            double(0.49289819222978415),
                                            double(0.47139673682599786),
                                            double(0.44961132965460687),
                                            double(0.42755509343028203),
                                            double(0.40524131400498992),
                                            double(0.38268343236508989),
                                            double(0.35989503653498833),
                                            double(0.33688985339222033),
                                            double(0.31368174039889141),
                                            double(0.29028467725446239),
                                            double(0.26671275747489848),
                                            double(0.24298017990326407),
                                            double(0.21910124015687005),
                                            double(0.19509032201612861),
                                            double(0.17096188876030122),
                                            double(0.1467304744553618),
                                            double(0.12241067519921635),
                                            double(0.098017140329560826),
                                            double(0.073564563599667732),
                                            double(0.049067674327417966),
                                            double(0.024541228522912326),
                                            double(0.0),
                                            double(-0.02454122852291208),
                                            double(-0.049067674327417724),
                                            double(-0.073564563599667496),
                                            double(-0.09801714032956059),
                                            double(-0.1224106751992161),
                                            double(-0.14673047445536158),
                                            double(-0.17096188876030097),
                                            double(-0.19509032201612836),
                                            double(-0.2191012401568698),
                                            double(-0.24298017990326382),
                                            double(-0.26671275747489825),
                                            double(-0.29028467725446211),
                                            double(-0.31368174039889118),
                                            double(-0.33688985339222011),
                                            double(-0.35989503653498811),
                                            double(-0.38268343236508967),
                                            double(-0.40524131400498969),
                                            double(-0.42755509343028181),
                                            double(-0.44961132965460665),
                                            double(-0.47139673682599764),
                                            double(-0.49289819222978393),
                                            double(-0.51410274419322155),
                                            double(-0.53499761988709693),
                                            double(-0.55557023301960196),
                                            double(-0.57580819141784534),
                                            double(-0.59569930449243325),
                                            double(-0.61523159058062671),
                                            double(-0.63439328416364527),
                                            double(-0.65317284295377653),
                                            double(-0.67155895484701844),
                                            double(-0.68954054473706683),
                                            double(-0.70710678118654746),
                                            double(-0.72424708295146678),
                                            double(-0.74095112535495888),
                                            double(-0.75720884650648423),
                                            double(-0.77301045336273666),
                                            double(-0.78834642762660589),
                                            double(-0.80320753148064505),
                                            double(-0.81758481315158382),
                                            double(-0.83146961230254524),
                                            double(-0.84485356524970701),
                                            double(-0.85772861000027201),
                                            double(-0.87008699110871135),
                                            double(-0.88192126434835494),
                                            double(-0.89322430119551521),
                                            double(-0.90398929312344312),
                                            double(-0.91420975570353047),
                                            double(-0.92387953251128652),
                                            double(-0.93299279883473896),
                                            double(-0.94154406518302081),
                                            double(-0.94952818059303667),
                                            double(-0.95694033573220882),
                                            double(-0.96377606579543984),
                                            double(-0.97003125319454397),
                                            double(-0.97570213003852846),
                                            double(-0.98078528040323032),
                                            double(-0.98527764238894111),
                                            double(-0.9891765099647809),
                                            double(-0.99247953459871008),
                                            double(-0.99518472667219693),
                                            double(-0.99729045667869021),
                                            double(-0.99879545620517241),
                                            double(-0.99969881869620425),
                                            double(-1.0),
                                            double(-0.99969881869620425),
                                            double(-0.99879545620517241),
                                            double(-0.99729045667869021),
                                            double(-0.99518472667219693),
                                            double(-0.99247953459871008),
                                            double(-0.9891765099647809),
                                            double(-0.98527764238894122),
                                            double(-0.98078528040323043),
                                            double(-0.97570213003852857),
                                            double(-0.97003125319454397),
                                            double(-0.96377606579543995),
                                            double(-0.95694033573220894),
                                            double(-0.94952818059303679),
                                            double(-0.94154406518302092),
                                            double(-0.93299279883473907),
                                            double(-0.92387953251128663),
                                            double(-0.91420975570353058),
                                            double(-0.90398929312344334),
                                            double(-0.89322430119551532),
                                            double(-0.88192126434835505),
                                            double(-0.87008699110871146),
                                            double(-0.85772861000027223),
                                            double(-0.84485356524970723),
                                            double(-0.83146961230254546),
                                            double(-0.81758481315158404),
                                            double(-0.80320753148064528),
                                            double(-0.78834642762660612),
                                            double(-0.77301045336273688),
                                            double(-0.75720884650648457),
                                            double(-0.74095112535495911),
                                            double(-0.724247082951467),
                                            double(-0.70710678118654768),
                                            double(-0.68954054473706716),
                                            double(-0.67155895484701866),
                                            double(-0.65317284295377709),
                                            double(-0.63439328416364593),
                                            double(-0.61523159058062737),
                                            double(-0.59569930449243325),
                                            double(-0.57580819141784523),
                                            double(-0.55557023301960218),
                                            double(-0.53499761988709726),
                                            double(-0.51410274419322188),
                                            double(-0.49289819222978426),
                                            double(-0.47139673682599792),
                                            double(-0.44961132965460698),
                                            double(-0.42755509343028253),
                                            double(-0.40524131400499042),
                                            double(-0.38268343236509039),
                                            double(-0.359895036534988),
                                            double(-0.33688985339222),
                                            double(-0.31368174039889152),
                                            double(-0.2902846772544625),
                                            double(-0.26671275747489859),
                                            double(-0.24298017990326418),
                                            double(-0.21910124015687016),
                                            double(-0.19509032201612872),
                                            double(-0.17096188876030177),
                                            double(-0.14673047445536239),
                                            double(-0.12241067519921603),
                                            double(-0.098017140329560506),
                                            double(-0.073564563599667412),
                                            double(-0.049067674327418091),
                                            double(-0.024541228522912448)};

}// namespace Math
}// namespace Utility
}// namespace Lite
