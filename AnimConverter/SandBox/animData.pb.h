// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: animData.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_animData_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_animData_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include "boneData.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_animData_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_animData_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
class animData_proto;
struct animData_protoDefaultTypeInternal;
extern animData_protoDefaultTypeInternal _animData_proto_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::animData_proto* Arena::CreateMaybeMessage<::animData_proto>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class animData_proto final :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:animData_proto) */ {
 public:
  inline animData_proto() : animData_proto(nullptr) {}
  ~animData_proto() override;
  explicit constexpr animData_proto(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  animData_proto(const animData_proto& from);
  animData_proto(animData_proto&& from) noexcept
    : animData_proto() {
    *this = ::std::move(from);
  }

  inline animData_proto& operator=(const animData_proto& from) {
    CopyFrom(from);
    return *this;
  }
  inline animData_proto& operator=(animData_proto&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const animData_proto& default_instance() {
    return *internal_default_instance();
  }
  static inline const animData_proto* internal_default_instance() {
    return reinterpret_cast<const animData_proto*>(
               &_animData_proto_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(animData_proto& a, animData_proto& b) {
    a.Swap(&b);
  }
  inline void Swap(animData_proto* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(animData_proto* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline animData_proto* New() const final {
    return new animData_proto();
  }

  animData_proto* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<animData_proto>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)  final;
  void CopyFrom(const animData_proto& from);
  void MergeFrom(const animData_proto& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(animData_proto* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "animData_proto";
  }
  protected:
  explicit animData_proto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBoneDataFieldNumber = 1,
    kParentFieldNumber = 2,
    kFrameBucketCountFieldNumber = 3,
  };
  // repeated .boneData_proto bone_Data = 1;
  int bone_data_size() const;
  private:
  int _internal_bone_data_size() const;
  public:
  void clear_bone_data();
  ::boneData_proto* mutable_bone_data(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::boneData_proto >*
      mutable_bone_data();
  private:
  const ::boneData_proto& _internal_bone_data(int index) const;
  ::boneData_proto* _internal_add_bone_data();
  public:
  const ::boneData_proto& bone_data(int index) const;
  ::boneData_proto* add_bone_data();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::boneData_proto >&
      bone_data() const;

  // sint32 parent = 2;
  void clear_parent();
  ::PROTOBUF_NAMESPACE_ID::int32 parent() const;
  void set_parent(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_parent() const;
  void _internal_set_parent(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // uint32 frameBucketCount = 3;
  void clear_framebucketcount();
  ::PROTOBUF_NAMESPACE_ID::uint32 framebucketcount() const;
  void set_framebucketcount(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_framebucketcount() const;
  void _internal_set_framebucketcount(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:animData_proto)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::boneData_proto > bone_data_;
  ::PROTOBUF_NAMESPACE_ID::int32 parent_;
  ::PROTOBUF_NAMESPACE_ID::uint32 framebucketcount_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_animData_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// animData_proto

// repeated .boneData_proto bone_Data = 1;
inline int animData_proto::_internal_bone_data_size() const {
  return bone_data_.size();
}
inline int animData_proto::bone_data_size() const {
  return _internal_bone_data_size();
}
inline ::boneData_proto* animData_proto::mutable_bone_data(int index) {
  // @@protoc_insertion_point(field_mutable:animData_proto.bone_Data)
  return bone_data_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::boneData_proto >*
animData_proto::mutable_bone_data() {
  // @@protoc_insertion_point(field_mutable_list:animData_proto.bone_Data)
  return &bone_data_;
}
inline const ::boneData_proto& animData_proto::_internal_bone_data(int index) const {
  return bone_data_.Get(index);
}
inline const ::boneData_proto& animData_proto::bone_data(int index) const {
  // @@protoc_insertion_point(field_get:animData_proto.bone_Data)
  return _internal_bone_data(index);
}
inline ::boneData_proto* animData_proto::_internal_add_bone_data() {
  return bone_data_.Add();
}
inline ::boneData_proto* animData_proto::add_bone_data() {
  ::boneData_proto* _add = _internal_add_bone_data();
  // @@protoc_insertion_point(field_add:animData_proto.bone_Data)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::boneData_proto >&
animData_proto::bone_data() const {
  // @@protoc_insertion_point(field_list:animData_proto.bone_Data)
  return bone_data_;
}

// sint32 parent = 2;
inline void animData_proto::clear_parent() {
  parent_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 animData_proto::_internal_parent() const {
  return parent_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 animData_proto::parent() const {
  // @@protoc_insertion_point(field_get:animData_proto.parent)
  return _internal_parent();
}
inline void animData_proto::_internal_set_parent(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  parent_ = value;
}
inline void animData_proto::set_parent(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_parent(value);
  // @@protoc_insertion_point(field_set:animData_proto.parent)
}

// uint32 frameBucketCount = 3;
inline void animData_proto::clear_framebucketcount() {
  framebucketcount_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 animData_proto::_internal_framebucketcount() const {
  return framebucketcount_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 animData_proto::framebucketcount() const {
  // @@protoc_insertion_point(field_get:animData_proto.frameBucketCount)
  return _internal_framebucketcount();
}
inline void animData_proto::_internal_set_framebucketcount(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  framebucketcount_ = value;
}
inline void animData_proto::set_framebucketcount(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_framebucketcount(value);
  // @@protoc_insertion_point(field_set:animData_proto.frameBucketCount)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_animData_2eproto
