#include "google/protobuf/unknown_field_set.h"
#include "google/protobuf/wire_format.h"
#include "iostream"
#include "main.pb.h"

#define PrintMsg(msg) \
  std::cout << #msg << ": " << msg.ShortDebugString() << "\n"

namespace explore {

constexpr int32_t kUnknownFieldSetSerializeMaxSize = 1 * 1024 * 1024;

std::string SerializeUnknownMessage(
    const google::protobuf::UnknownFieldSet& ufs) {
  static char s_unknown_seri_buf[kUnknownFieldSetSerializeMaxSize];
  uint8_t* start = reinterpret_cast<uint8_t*>(s_unknown_seri_buf);
  uint8_t* end =
      google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
          ufs, start);

  if ((end - start < 0) || (end - start > kUnknownFieldSetSerializeMaxSize)) {
    printf("serialize failed");
    return "";  // 如果序列化出现问题, 返回空, 表现上是部分数据丢失
  }

  return std::string(start, end);
}

int test_main() {
  EmptyMessage empty_msg;
  Test t;
  t.set_i32(123);
  empty_msg.ParseFromString(t.SerializeAsString());

  google::protobuf::UnknownFieldSet* ufs;
  const google::protobuf::Descriptor* em_desc = empty_msg.GetDescriptor();
  const google::protobuf::Reflection* em_reflect = empty_msg.GetReflection();
  ufs = em_reflect->MutableUnknownFields(&empty_msg);
  ufs->AddVarint(2, 48);
  PrintMsg(empty_msg);
  t.ParseFromString(SerializeUnknownMessage(*ufs));
  PrintMsg(t);
  t.ParseFromString(empty_msg.SerializeAsString());
  PrintMsg(t);
  return 0;
}
}  // namespace explore

int main() { return explore::test_main(); }
