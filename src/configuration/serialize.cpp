#include "cborserializestream.h"
#include "jsonserializestream.h"
#include "xmlserializestream.h"
#include <serialize.h>


namespace m2 {


GsSerializeStreamPtr GsSerializeStreamFactory::CreateStream(GsSerializeStreamType eType)
{
    return GsSerializeStreamPtr();
}

}// namespace m2
