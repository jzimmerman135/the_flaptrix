PROTO_OBJ=proto.o proto/main.o proto/lib/cJSON/cJSON.o
CFLAGS+=-g

proto_clean:
	$(RM) gameproto $(PROTO_OBJ)
