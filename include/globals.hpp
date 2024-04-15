#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <vector>

using std::string;

#define DATA_SIZE 100
#define NTHREADS 1
#define TIMETORUN 30


extern volatile 
int done;
// Add your constant declarations here

const int VECTOR_SIZE = 102; // The size of the vector
const int QUERY_SIZE = 104; // The size of the query type
; // The size of the data without the timestamp and c
const int K = 100; // The number of nearest neighbors to find
const string DATA_FILE = "../data/dummy-data.bin"; // The path to the data file
const string QUERY_FILE = "../data/dummy-query.bin"; // The path to the query file
const string OUTPUT_FILE = "../output.bin"; // The path to the output file

const std::vector<float> BREAK_POINTS_2 = {0.0};
const std::vector<float> BREAK_POINTS_3 = {-0.43072729929545756,0.43072729929545744,};
const std::vector<float> BREAK_POINTS_8 = {-1.1503493803760079,-0.6744897501960817,-0.31863936396437514,0.0,0.31863936396437514,0.6744897501960817,1.1503493803760079,};
const std::vector<float> BREAK_POINTS_16 = {-1.5341205443525463,-1.1503493803760079,-0.887146559018876,-0.6744897501960817,-0.4887764111146695,-0.31863936396437514,-0.1573106846101707,0.0,0.1573106846101707,0.31863936396437514,0.4887764111146695,0.6744897501960817,0.887146559018876,1.1503493803760079,1.5341205443525463,};
const std::vector<float> BREAK_POINTS_32 = {-1.8627318674216515,-1.5341205443525463,-1.318010897303537,-1.1503493803760079,-1.009990169249582,-0.887146559018876,-0.7764217611479277,-0.6744897501960817,-0.579132162255556,-0.4887764111146695,-0.40225006532172536,-0.31863936396437514,-0.23720210932878769,-0.1573106846101707,-0.0784124127331122,0.0,0.0784124127331122,0.1573106846101707,0.23720210932878769,0.31863936396437514,0.40225006532172536,0.4887764111146695,0.579132162255556,0.6744897501960817,0.7764217611479277,0.887146559018876,1.009990169249582,1.1503493803760079,1.318010897303537,1.5341205443525463,1.8627318674216515,};
const std::vector<float> BREAK_POINTS_64 = {-2.1538746940614564,-1.8627318674216515,-1.6759397227734438,-1.5341205443525463,-1.417797137996267,-1.318010897303537,-1.229858759216589,-1.1503493803760079,-1.0775155670402803,-1.009990169249582,-0.9467817563010457,-0.887146559018876,-0.8305108782053993,-0.7764217611479277,-0.7245143834923654,-0.6744897501960817,-0.6260990123464212,-0.579132162255556,-0.5334097062412806,-0.4887764111146695,-0.4450965249855164,-0.40225006532172536,-0.36012989178956945,-0.31863936396437514,-0.27769043982157676,-0.23720210932878769,-0.1970990842943123,-0.1573106846101707,-0.1177698745790953,-0.0784124127331122,-0.039176085503097625,0.0,0.039176085503097625,0.0784124127331122,0.1177698745790953,0.1573106846101707,0.1970990842943123,0.23720210932878769,0.27769043982157676,0.31863936396437514,0.36012989178956945,0.40225006532172536,0.4450965249855164,0.4887764111146695,0.5334097062412806,0.579132162255556,0.6260990123464212,0.6744897501960817,0.7245143834923654,0.7764217611479277,0.8305108782053993,0.887146559018876,0.9467817563010457,1.009990169249582,1.0775155670402803,1.1503493803760079,1.229858759216589,1.318010897303537,1.417797137996267,1.5341205443525463,1.6759397227734438,1.8627318674216515,2.1538746940614564,};
const std::vector<float> BREAK_POINTS_128 = {-2.4175590162365053,-2.1538746940614564,-1.987427885929896,-1.8627318674216515,-1.7616704103630672,-1.6759397227734438,-1.6010086648860757,-1.5341205443525463,-1.4734675779471014,-1.417797137996267,-1.3662038163720982,-1.318010897303537,-1.2726986411905359,-1.229858759216589,-1.189164350199337,-1.1503493803760079,-1.1131942771609284,-1.0775155670402803,-1.0431582633184535,-1.009990169249582,-0.9778975439405418,-0.9467817563010457,-0.9165566675331127,-0.887146559018876,-0.8584844741418323,-0.8305108782053993,-0.8031725655979178,-0.7764217611479277,-0.7502153754679406,-0.7245143834923654,-0.6992833023832199,-0.6744897501960817,-0.6501040706479952,-0.6260990123464212,-0.6024494531644237,-0.579132162255556,-0.5561255936186914,-0.5334097062412806,-0.5109658067382474,-0.4887764111146695,-0.46682512285258965,-0.4450965249855164,-0.4235760842011997,-0.40225006532172536,-0.3811054547635565,-0.36012989178956945,-0.3393116065388172,-0.31863936396437514,-0.29810241293048684,-0.27769043982157676,-0.2573935261009383,-0.23720210932878769,-0.21710694721012977,-0.1970990842943123,-0.17716982099173983,-0.1573106846101707,-0.1375134021443359,-0.1177698745790953,-0.09807215248866107,-0.0784124127331122,-0.05878293606894307,-0.039176085503097625,-0.01958428523012692,0.0,0.01958428523012692,0.039176085503097625,0.05878293606894307,0.0784124127331122,0.09807215248866107,0.1177698745790953,0.1375134021443359,0.1573106846101707,0.17716982099173983,0.1970990842943123,0.21710694721012977,0.23720210932878769,0.2573935261009383,0.27769043982157676,0.29810241293048684,0.31863936396437514,0.3393116065388172,0.36012989178956945,0.3811054547635565,0.40225006532172536,0.4235760842011997,0.4450965249855164,0.46682512285258965,0.4887764111146695,0.5109658067382474,0.5334097062412806,0.5561255936186914,0.579132162255556,0.6024494531644237,0.6260990123464212,0.6501040706479952,0.6744897501960817,0.6992833023832199,0.7245143834923654,0.7502153754679406,0.7764217611479277,0.8031725655979178,0.8305108782053993,0.8584844741418323,0.887146559018876,0.9165566675331127,0.9467817563010457,0.9778975439405418,1.009990169249582,1.0431582633184535,1.0775155670402803,1.1131942771609284,1.1503493803760079,1.189164350199337,1.229858759216589,1.2726986411905359,1.318010897303537,1.3662038163720982,1.417797137996267,1.4734675779471014,1.5341205443525463,1.6010086648860757,1.6759397227734438,1.7616704103630672,1.8627318674216515,1.987427885929896,2.1538746940614564,2.4175590162365053,};
const std::vector<float> BREAK_POINTS_256 = {-2.6600674686174592,-2.4175590162365053,-2.2662268092096527,-2.1538746940614564,-2.063527898316244,-1.987427885929896,-1.9213507742937037,-1.8627318674216515,-1.8098922384806087,-1.7616704103630672,-1.7172281175057411,-1.6759397227734438,-1.6373253827680638,-1.6010086648860757,-1.5666885860684134,-1.5341205443525463,-1.5031029431292742,-1.4734675779471014,-1.4450725798180741,-1.417797137996267,-1.3915374879959002,-1.3662038163720982,-1.341717841080254,-1.318010897303537,-1.2950224067058145,-1.2726986411905359,-1.2509917154625452,-1.229858759216589,-1.209261231709155,-1.189164350199337,-1.1695366102071425,-1.1503493803760079,-1.1315765583861879,-1.1131942771609284,-1.095180652761388,-1.0775155670402803,-1.060180479435355,-1.0431582633184535,-1.0264330631379104,-1.009990169249582,-0.993815907860883,-0.9778975439405418,-0.9622231952954207,-0.9467817563010457,-0.9315628300071144,-0.9165566675331127,-0.9017541138301001,-0.887146559018876,-0.8727258946270401,-0.8584844741418323,-0.8444150773752573,-0.8305108782053993,-0.816765415315091,-0.8031725655979178,-0.7897265199432659,-0.7764217611479277,-0.7632530437325705,-0.7502153754679406,-0.7373040004386543,-0.7245143834923654,-0.7118421959394191,-0.6992833023832199,-0.6868337485747306,-0.6744897501960817,-0.6622476824884141,-0.6501040706479952,-0.638055580922517,-0.6260990123464212,-0.6142312890602453,-0.6024494531644237,-0.5907506580628188,-0.579132162255556,-0.5675913235445692,-0.5561255936186914,-0.5447325129881758,-0.5334097062412806,-0.5221548775980015,-0.5109658067382474,-0.49984034488373513,-0.4887764111146695,-0.477771988903886,-0.46682512285258965,-0.4559339156131388,-0.4450965249855164,-0.4343111611752096,-0.4235760842011997,-0.4128896014436543,-0.40225006532172536,-0.3916558710925915,-0.3811054547635565,-0.37059729110962925,-0.36012989178956945,-0.34970180355389524,-0.3393116065388172,-0.32895791264049107,-0.31863936396437514,-0.30835463134483726,-0.29810241293048684,-0.2878814328310118,-0.27769043982157676,-0.2675282061010972,-0.2573935261009383,-0.2472852153408049,-0.23720210932878769,-0.22714306250271532,-0.21710694721012977,-0.2070926527243603,-0.1970990842943123,-0.18712516222572084,-0.17716982099173983,-0.1672320083708501,-0.1573106846101707,-0.14740482161235485,-0.1375134021443359,-0.12763541906627032,-0.1177698745790953,-0.10791577948918656,-0.09807215248866107,-0.08823801944992446,-0.0784124127331122,-0.06859437050511812,-0.05878293606894307,-0.04897715720213194,-0.039176085503097625,-0.02937877574415705,-0.01958428523012692,-0.009791673161345346,0.0,0.009791673161345346,0.01958428523012692,0.02937877574415705,0.039176085503097625,0.04897715720213194,0.05878293606894307,0.06859437050511812,0.0784124127331122,0.08823801944992446,0.09807215248866107,0.10791577948918656,0.1177698745790953,0.12763541906627032,0.1375134021443359,0.14740482161235485,0.1573106846101707,0.1672320083708501,0.17716982099173983,0.18712516222572084,0.1970990842943123,0.2070926527243603,0.21710694721012977,0.22714306250271532,0.23720210932878769,0.2472852153408049,0.2573935261009383,0.2675282061010972,0.27769043982157676,0.2878814328310118,0.29810241293048684,0.30835463134483726,0.31863936396437514,0.32895791264049107,0.3393116065388172,0.34970180355389524,0.36012989178956945,0.37059729110962925,0.3811054547635565,0.3916558710925915,0.40225006532172536,0.4128896014436543,0.4235760842011997,0.4343111611752096,0.4450965249855164,0.4559339156131388,0.46682512285258965,0.477771988903886,0.4887764111146695,0.49984034488373513,0.5109658067382474,0.5221548775980015,0.5334097062412806,0.5447325129881758,0.5561255936186914,0.5675913235445692,0.579132162255556,0.5907506580628188,0.6024494531644237,0.6142312890602453,0.6260990123464212,0.638055580922517,0.6501040706479952,0.6622476824884141,0.6744897501960817,0.6868337485747306,0.6992833023832199,0.7118421959394191,0.7245143834923654,0.7373040004386543,0.7502153754679406,0.7632530437325705,0.7764217611479277,0.7897265199432659,0.8031725655979178,0.816765415315091,0.8305108782053993,0.8444150773752573,0.8584844741418323,0.8727258946270401,0.887146559018876,0.9017541138301001,0.9165566675331127,0.9315628300071144,0.9467817563010457,0.9622231952954207,0.9778975439405418,0.993815907860883,1.009990169249582,1.0264330631379104,1.0431582633184535,1.060180479435355,1.0775155670402803,1.095180652761388,1.1131942771609284,1.1315765583861879,1.1503493803760079,1.1695366102071425,1.189164350199337,1.209261231709155,1.229858759216589,1.2509917154625452,1.2726986411905359,1.2950224067058145,1.318010897303537,1.341717841080254,1.3662038163720982,1.3915374879959002,1.417797137996267,1.4450725798180741,1.4734675779471014,1.5031029431292742,1.5341205443525463,1.5666885860684134,1.6010086648860757,1.6373253827680638,1.6759397227734438,1.7172281175057411,1.7616704103630672,1.8098922384806087,1.8627318674216515,1.9213507742937037,1.987427885929896,2.063527898316244,2.1538746940614564,2.2662268092096527,2.4175590162365053,2.6600674686174592,};
const std::vector<float> BREAK_POINTS_512 = {-2.8856349124267573,-2.6600674686174592,-2.5205022171903595,-2.4175590162365053,-2.3352330400688133,-2.2662268092096527,-2.206575216537129,-2.1538746940614564,-2.1065540881628144,-2.063527898316244,-2.024013623719158,-1.987427885929896,-1.9533237077453942,-1.9213507742937037,-1.891229237820108,-1.8627318674216515,-1.8356715369125434,-1.8098922384806087,-1.7852624904353236,-1.7616704103630672,-1.7390199717299037,-1.7172281175057411,-1.6962225050066093,-1.6759397227734438,-1.6563238653408074,-1.6373253827680638,-1.6189001435373596,-1.6010086648860757,-1.5836154758017882,-1.5666885860684134,-1.5501990407917612,-1.5341205443525463,-1.5184291411525912,-1.5031029431292742,-1.4881218960233813,-1.4734675779471014,-1.4591230250215932,-1.4450725798180741,-1.431301759102476,-1.417797137996267,-1.4045462481588746,-1.3915374879959002,-1.3787600432219227,-1.3662038163720982,-1.3538593640751064,-1.341717841080254,-1.329770950181209,-1.318010897303537,-1.306430351127565,-1.2950224067058145,-1.2837805526081674,-1.2726986411905359,-1.2617708616359868,-1.2509917154625452,-1.2403559942306719,-1.229858759216589,-1.2194953228462238,-1.209261231709155,-1.199152250993274,-1.189164350199337,-1.1792936900106505,-1.1695366102071425,-1.1598896185252787,-1.1503493803760079,-1.140912709342314,-1.1315765583861879,-1.1223380117021655,-1.1131942771609284,-1.1041426792922298,-1.095180652761388,-1.0863057362981006,-1.0775155670402803,-1.0688078752591985,-1.060180479435355,-1.0516312816573352,-1.0431582633184535,-1.0347594810882446,-1.0264330631379104,-1.0181772056006682,-1.009990169249582,-1.001870276376982,-0.993815907860883,-0.9858255004050612,-0.9778975439405418,-0.9700305791772408,-0.9622231952954207,-0.9544740277674426,-0.9467817563010457,-0.9391451028960622,-0.9315628300071144,-0.924033738805388,-0.9165566675331127,-0.909130489944847,-0.9017541138301001,-0.894426479612224,-0.887146559018876,-0.8799133538196812,-0.8727258946270401,-0.8655832397563085,-0.8584844741418323,-0.8514287083055712,-0.8444150773752573,-0.8374427401492454,-0.8305108782053993,-0.8236186950515331,-0.816765415315091,-0.8099502839698922,-0.8031725655979178,-0.7964315436842329,-0.7897265199432659,-0.7830568136747741,-0.7764217611479277,-0.7698207150120411,-0.7632530437325705,-0.7567181310510782,-0.7502153754679406,-0.7437441897466541,-0.7373040004386543,-0.7308942474276288,-0.7245143834923654,-0.7181638738872306,-0.7118421959394191,-0.7055488386621755,-0.6992833023832199,-0.6930450983876636,-0.6868337485747306,-0.6806487851276465,-0.6744897501960817,-0.668356195590579,-0.6622476824884141,-0.6561637811503791,-0.6501040706479952,-0.6440681386006925,-0.638055580922517,-0.6320660015779467,-0.6260990123464212,-0.6201542325952075,-0.6142312890602453,-0.608329815634632,-0.6024494531644237,-0.5965898492514454,-0.5907506580628188,-0.5849315401469273,-0.579132162255556,-0.5733521971719525,-0.5675913235445692,-0.5618492257262567,-0.5561255936186914,-0.5504201225218275,-0.5447325129881758,-0.5390624706817188,-0.5334097062412806,-0.5277739351481803,-0.5221548775980015,-0.5165522583763212,-0.5109658067382474,-0.5053952562916195,-0.49984034488373513,-0.494300814491471,-0.4887764111146695,-0.4832668846726728,-0.477771988903886,-0.4722914812682607,-0.46682512285258965,-0.4613726782785132,-0.4559339156131388,-0.45050860628217826,-0.4450965249855164,-0.43969744961512014,-0.4343111611752096,-0.4289374437046087,-0.4235760842011997,-0.4182268725484093,-0.4128896014436543,-0.40756406632867975,-0.40225006532172536,-0.3969473991514547,-0.3916558710925915,-0.38637528690319967,-0.3811054547635565,-0.3758461852165611,-0.37059729110962925,-0.3653585875380232,-0.36012989178956945,-0.3549110232907174,-0.34970180355389524,-0.3445020561261196,-0.3393116065388172,-0.3341302822588196,-0.32895791264049107,-0.32379432887895426,-0.31863936396437514,-0.3134928526372756,-0.30835463134483726,-0.30322453819816625,-0.29810241293048684,-0.29298809685623334,-0.2878814328310118,-0.2827822652124026,-0.27769043982157676,-0.2726058039056999,-0.2675282061010972,-0.26245749639715554,-0.2573935261009383,-0.25233614780248953,-0.2472852153408049,-0.24224058377044752,-0.23720210932878769,-0.23216964940384524,-0.22714306250271532,-0.22212220822055745,-0.21710694721012977,-0.21209714115184913,-0.2070926527243603,-0.2020933455755962,-0.1970990842943123,-0.19210973438208,-0.18712516222572084,-0.18214523507016814,-0.17716982099173983,-0.17219878887180795,-0.1672320083708501,-0.16226934990286979,-0.1573106846101707,-0.15235588433847255,-0.14740482161235485,-0.1424573696110161,-0.1375134021443359,-0.13257279362922775,-0.12763541906627032,-0.12270115401660613,-0.1177698745790953,-0.11284145736771417,-0.10791577948918656,-0.10299271852083793,-0.09807215248866107,-0.09315395984558328,-0.08823801944992446,-0.08332421054403628,-0.0784124127331122,-0.07350250596415873,-0.06859437050511812,-0.06368788692413291,-0.05878293606894307,-0.05387939904640625,-0.04897715720213194,-0.04407609210022043,-0.039176085503097625,-0.03427701935143659,-0.02937877574415705,-0.024481236918494062,-0.01958428523012692,-0.014687803133359814,-0.009791673161345346,-0.004895777906342452,0.0,0.004895777906342452,0.009791673161345346,0.014687803133359814,0.01958428523012692,0.024481236918494062,0.02937877574415705,0.03427701935143659,0.039176085503097625,0.04407609210022043,0.04897715720213194,0.05387939904640625,0.05878293606894307,0.06368788692413291,0.06859437050511812,0.07350250596415873,0.0784124127331122,0.08332421054403628,0.08823801944992446,0.09315395984558328,0.09807215248866107,0.10299271852083793,0.10791577948918656,0.11284145736771417,0.1177698745790953,0.12270115401660613,0.12763541906627032,0.13257279362922775,0.1375134021443359,0.1424573696110161,0.14740482161235485,0.15235588433847255,0.1573106846101707,0.16226934990286979,0.1672320083708501,0.17219878887180795,0.17716982099173983,0.18214523507016814,0.18712516222572084,0.19210973438208,0.1970990842943123,0.2020933455755962,0.2070926527243603,0.21209714115184913,0.21710694721012977,0.22212220822055745,0.22714306250271532,0.23216964940384524,0.23720210932878769,0.24224058377044752,0.2472852153408049,0.25233614780248953,0.2573935261009383,0.26245749639715554,0.2675282061010972,0.2726058039056999,0.27769043982157676,0.2827822652124026,0.2878814328310118,0.29298809685623334,0.29810241293048684,0.30322453819816625,0.30835463134483726,0.3134928526372756,0.31863936396437514,0.32379432887895426,0.32895791264049107,0.3341302822588196,0.3393116065388172,0.3445020561261196,0.34970180355389524,0.3549110232907174,0.36012989178956945,0.3653585875380232,0.37059729110962925,0.3758461852165611,0.3811054547635565,0.38637528690319967,0.3916558710925915,0.3969473991514547,0.40225006532172536,0.40756406632867975,0.4128896014436543,0.4182268725484093,0.4235760842011997,0.4289374437046087,0.4343111611752096,0.43969744961512014,0.4450965249855164,0.45050860628217826,0.4559339156131388,0.4613726782785132,0.46682512285258965,0.4722914812682607,0.477771988903886,0.4832668846726728,0.4887764111146695,0.494300814491471,0.49984034488373513,0.5053952562916195,0.5109658067382474,0.5165522583763212,0.5221548775980015,0.5277739351481803,0.5334097062412806,0.5390624706817188,0.5447325129881758,0.5504201225218275,0.5561255936186914,0.5618492257262567,0.5675913235445692,0.5733521971719525,0.579132162255556,0.5849315401469273,0.5907506580628188,0.5965898492514454,0.6024494531644237,0.608329815634632,0.6142312890602453,0.6201542325952075,0.6260990123464212,0.6320660015779467,0.638055580922517,0.6440681386006925,0.6501040706479952,0.6561637811503791,0.6622476824884141,0.668356195590579,0.6744897501960817,0.6806487851276465,0.6868337485747306,0.6930450983876636,0.6992833023832199,0.7055488386621755,0.7118421959394191,0.7181638738872306,0.7245143834923654,0.7308942474276288,0.7373040004386543,0.7437441897466541,0.7502153754679406,0.7567181310510782,0.7632530437325705,0.7698207150120411,0.7764217611479277,0.7830568136747741,0.7897265199432659,0.7964315436842329,0.8031725655979178,0.8099502839698922,0.816765415315091,0.8236186950515331,0.8305108782053993,0.8374427401492454,0.8444150773752573,0.8514287083055712,0.8584844741418323,0.8655832397563085,0.8727258946270401,0.8799133538196812,0.887146559018876,0.894426479612224,0.9017541138301001,0.909130489944847,0.9165566675331127,0.924033738805388,0.9315628300071144,0.9391451028960622,0.9467817563010457,0.9544740277674426,0.9622231952954207,0.9700305791772408,0.9778975439405418,0.9858255004050612,0.993815907860883,1.001870276376982,1.009990169249582,1.0181772056006682,1.0264330631379104,1.0347594810882446,1.0431582633184535,1.0516312816573352,1.060180479435355,1.0688078752591985,1.0775155670402803,1.0863057362981006,1.095180652761388,1.1041426792922298,1.1131942771609284,1.1223380117021655,1.1315765583861879,1.140912709342314,1.1503493803760079,1.1598896185252787,1.1695366102071425,1.1792936900106505,1.189164350199337,1.199152250993274,1.209261231709155,1.2194953228462238,1.229858759216589,1.2403559942306719,1.2509917154625452,1.2617708616359868,1.2726986411905359,1.2837805526081674,1.2950224067058145,1.306430351127565,1.318010897303537,1.329770950181209,1.341717841080254,1.3538593640751064,1.3662038163720982,1.3787600432219227,1.3915374879959002,1.4045462481588746,1.417797137996267,1.431301759102476,1.4450725798180741,1.4591230250215932,1.4734675779471014,1.4881218960233813,1.5031029431292742,1.5184291411525912,1.5341205443525463,1.5501990407917612,1.5666885860684134,1.5836154758017882,1.6010086648860757,1.6189001435373596,1.6373253827680638,1.6563238653408074,1.6759397227734438,1.6962225050066093,1.7172281175057411,1.7390199717299037,1.7616704103630672,1.7852624904353236,1.8098922384806087,1.8356715369125434,1.8627318674216515,1.891229237820108,1.9213507742937037,1.9533237077453942,1.987427885929896,2.024013623719158,2.063527898316244,2.1065540881628144,2.1538746940614564,2.206575216537129,2.2662268092096527,2.3352330400688133,2.4175590162365053,2.5205022171903595,2.6600674686174592,2.8856349124267573,};

#endif // CONSTANTS_HPP
