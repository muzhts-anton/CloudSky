// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: KeyboardMouseMessage.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_KeyboardMouseMessage_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_KeyboardMouseMessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019000 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_KeyboardMouseMessage_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_KeyboardMouseMessage_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_KeyboardMouseMessage_2eproto;
namespace KeyboardMouse {
class ButtonsCoords;
struct ButtonsCoordsDefaultTypeInternal;
extern ButtonsCoordsDefaultTypeInternal _ButtonsCoords_default_instance_;
}  // namespace KeyboardMouse
PROTOBUF_NAMESPACE_OPEN
template<> ::KeyboardMouse::ButtonsCoords* Arena::CreateMaybeMessage<::KeyboardMouse::ButtonsCoords>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace KeyboardMouse {

// ===================================================================

class ButtonsCoords final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:KeyboardMouse.ButtonsCoords) */ {
 public:
  inline ButtonsCoords() : ButtonsCoords(nullptr) {}
  ~ButtonsCoords() override;
  explicit constexpr ButtonsCoords(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ButtonsCoords(const ButtonsCoords& from);
  ButtonsCoords(ButtonsCoords&& from) noexcept
    : ButtonsCoords() {
    *this = ::std::move(from);
  }

  inline ButtonsCoords& operator=(const ButtonsCoords& from) {
    CopyFrom(from);
    return *this;
  }
  inline ButtonsCoords& operator=(ButtonsCoords&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ButtonsCoords& default_instance() {
    return *internal_default_instance();
  }
  static inline const ButtonsCoords* internal_default_instance() {
    return reinterpret_cast<const ButtonsCoords*>(
               &_ButtonsCoords_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ButtonsCoords& a, ButtonsCoords& b) {
    a.Swap(&b);
  }
  inline void Swap(ButtonsCoords* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ButtonsCoords* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ButtonsCoords* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ButtonsCoords>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ButtonsCoords& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ButtonsCoords& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ButtonsCoords* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "KeyboardMouse.ButtonsCoords";
  }
  protected:
  explicit ButtonsCoords(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kButtonPressedFieldNumber = 1,
    kXCoordFieldNumber = 2,
    kYCoordFieldNumber = 3,
  };
  // repeated bool buttonPressed = 1 [packed = true];
  int buttonpressed_size() const;
  private:
  int _internal_buttonpressed_size() const;
  public:
  void clear_buttonpressed();
  private:
  bool _internal_buttonpressed(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
      _internal_buttonpressed() const;
  void _internal_add_buttonpressed(bool value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
      _internal_mutable_buttonpressed();
  public:
  bool buttonpressed(int index) const;
  void set_buttonpressed(int index, bool value);
  void add_buttonpressed(bool value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
      buttonpressed() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
      mutable_buttonpressed();

  // int64 xCoord = 2;
  void clear_xcoord();
  int64_t xcoord() const;
  void set_xcoord(int64_t value);
  private:
  int64_t _internal_xcoord() const;
  void _internal_set_xcoord(int64_t value);
  public:

  // int64 yCoord = 3;
  void clear_ycoord();
  int64_t ycoord() const;
  void set_ycoord(int64_t value);
  private:
  int64_t _internal_ycoord() const;
  void _internal_set_ycoord(int64_t value);
  public:

  // @@protoc_insertion_point(class_scope:KeyboardMouse.ButtonsCoords)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool > buttonpressed_;
  int64_t xcoord_;
  int64_t ycoord_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_KeyboardMouseMessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ButtonsCoords

// repeated bool buttonPressed = 1 [packed = true];
inline int ButtonsCoords::_internal_buttonpressed_size() const {
  return buttonpressed_.size();
}
inline int ButtonsCoords::buttonpressed_size() const {
  return _internal_buttonpressed_size();
}
inline void ButtonsCoords::clear_buttonpressed() {
  buttonpressed_.Clear();
}
inline bool ButtonsCoords::_internal_buttonpressed(int index) const {
  return buttonpressed_.Get(index);
}
inline bool ButtonsCoords::buttonpressed(int index) const {
  // @@protoc_insertion_point(field_get:KeyboardMouse.ButtonsCoords.buttonPressed)
  return _internal_buttonpressed(index);
}
inline void ButtonsCoords::set_buttonpressed(int index, bool value) {
  buttonpressed_.Set(index, value);
  // @@protoc_insertion_point(field_set:KeyboardMouse.ButtonsCoords.buttonPressed)
}
inline void ButtonsCoords::_internal_add_buttonpressed(bool value) {
  buttonpressed_.Add(value);
}
inline void ButtonsCoords::add_buttonpressed(bool value) {
  _internal_add_buttonpressed(value);
  // @@protoc_insertion_point(field_add:KeyboardMouse.ButtonsCoords.buttonPressed)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
ButtonsCoords::_internal_buttonpressed() const {
  return buttonpressed_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >&
ButtonsCoords::buttonpressed() const {
  // @@protoc_insertion_point(field_list:KeyboardMouse.ButtonsCoords.buttonPressed)
  return _internal_buttonpressed();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
ButtonsCoords::_internal_mutable_buttonpressed() {
  return &buttonpressed_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< bool >*
ButtonsCoords::mutable_buttonpressed() {
  // @@protoc_insertion_point(field_mutable_list:KeyboardMouse.ButtonsCoords.buttonPressed)
  return _internal_mutable_buttonpressed();
}

// int64 xCoord = 2;
inline void ButtonsCoords::clear_xcoord() {
  xcoord_ = int64_t{0};
}
inline int64_t ButtonsCoords::_internal_xcoord() const {
  return xcoord_;
}
inline int64_t ButtonsCoords::xcoord() const {
  // @@protoc_insertion_point(field_get:KeyboardMouse.ButtonsCoords.xCoord)
  return _internal_xcoord();
}
inline void ButtonsCoords::_internal_set_xcoord(int64_t value) {
  
  xcoord_ = value;
}
inline void ButtonsCoords::set_xcoord(int64_t value) {
  _internal_set_xcoord(value);
  // @@protoc_insertion_point(field_set:KeyboardMouse.ButtonsCoords.xCoord)
}

// int64 yCoord = 3;
inline void ButtonsCoords::clear_ycoord() {
  ycoord_ = int64_t{0};
}
inline int64_t ButtonsCoords::_internal_ycoord() const {
  return ycoord_;
}
inline int64_t ButtonsCoords::ycoord() const {
  // @@protoc_insertion_point(field_get:KeyboardMouse.ButtonsCoords.yCoord)
  return _internal_ycoord();
}
inline void ButtonsCoords::_internal_set_ycoord(int64_t value) {
  
  ycoord_ = value;
}
inline void ButtonsCoords::set_ycoord(int64_t value) {
  _internal_set_ycoord(value);
  // @@protoc_insertion_point(field_set:KeyboardMouse.ButtonsCoords.yCoord)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace KeyboardMouse

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_KeyboardMouseMessage_2eproto
