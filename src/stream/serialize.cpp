#include "cborserializestream.h"
#include "jsonserializestream.h"
#include "xmlserializestream.h"
#include <serialize.h>


namespace Lite {
namespace Utility {


GsSerializeStreamPtr GsSerializeStreamFactory::CreateStream(GsSerializeStreamType eType)
{
    return GsSerializeStreamPtr();
}

}// namespace Utility
}// namespace Lite
