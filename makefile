
#-----------------------------------------------------------------------

APP           := XGame
TARGET        := OrderServer
CONFIG        := 
STRIP_FLAG    := N
TARS2CPP_FLAG := 
CFLAGS        += -lm -lz -lssl
CXXFLAGS      += -lm -lz -lssl

INCLUDE   += -I/usr/local/cpp_modules/curl/include
LIB       += -L/usr/local/cpp_modules/curl/lib -lcurl

INCLUDE   += -I/usr/local/cpp_modules/protobuf/include
LIB       += -L/usr/local/cpp_modules/protobuf/lib -lprotobuf 

INCLUDE   += -I/usr/local/cpp_modules/wbl/include
LIB       += -L/usr/local/cpp_modules/wbl/lib -lwbl

INCLUDE   += -I/usr/local/cpp_modules/rapidjson/include
LIB       += -L/usr/local/cpp_modules/rapidjson/lib

INCLUDE   += -I/usr/local/cpp_modules/uuid/include
LIB       += -L/usr/local/cpp_modules/uuid/lib -luuid

INCLUDE   += -I/usr/local/cpp_modules/jwt/include
LIB       += -L/usr/local/cpp_modules/jwt/lib

LIB	      += -lcrypto


#-----------------------------------------------------------------------
include /home/tarsproto/XGame/Comm/Comm.mk
include /home/tarsproto/XGame/util/util.mk
include /home/tarsproto/XGame/ActivityServer/ActivityServer.mk
include /home/tarsproto/XGame/RouterServer/RouterServer.mk
include /home/tarsproto/XGame/HallServer/HallServer.mk
include /home/tarsproto/XGame/protocols/protocols.mk
include /home/tarsproto/XGame/ConfigServer/ConfigServer.mk
include /home/tarsproto/XGame/DBAgentServer/DBAgentServer.mk
include /home/tarsproto/XGame/Log2DBServer/Log2DBServer.mk
include /home/tarsproto/XGame/OrderServer/OrderServer.mk
include /usr/local/tars/cpp/makefile/makefile.tars

#-----------------------------------------------------------------------
xgame:
	cp -f $(TARGET) /usr/local/app/tars/tarsnode/data/XGame.OrderServer/bin/
