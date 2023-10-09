#include "cborserializestream.h"
#include "jsonserializestream.h"
#include "xmlserializestream.h"
#include <serialize.h>


namespace m2 {


SerializeStreamPtr SerializeStreamFactory::CreateStream(SerializeStreamType eType)
{
    return SerializeStreamPtr();
}

}// namespace m2
