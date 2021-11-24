// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: KeyboardMouseMessage.proto

#include "KeyboardMouseMessage.pb.h"

#include <algorithm>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/wire_format_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace KeyboardMouse {
constexpr ButtonsCoords::ButtonsCoords(
    ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
    : buttonpressed_()
    , xcoord_(int64_t { 0 })
    , ycoord_(int64_t { 0 })
{
}
struct ButtonsCoordsDefaultTypeInternal {
    constexpr ButtonsCoordsDefaultTypeInternal()
        : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized {})
    {
    }
    ~ButtonsCoordsDefaultTypeInternal() { }
    union {
        ButtonsCoords _instance;
    };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ButtonsCoordsDefaultTypeInternal _ButtonsCoords_default_instance_;
} // namespace KeyboardMouse
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_KeyboardMouseMessage_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_KeyboardMouseMessage_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_KeyboardMouseMessage_2eproto = nullptr;

const uint32_t TableStruct_KeyboardMouseMessage_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    ~0u, // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::KeyboardMouse::ButtonsCoords, _internal_metadata_),
    ~0u, // no _extensions_
    ~0u, // no _oneof_case_
    ~0u, // no _weak_field_map_
    ~0u, // no _inlined_string_donated_
    PROTOBUF_FIELD_OFFSET(::KeyboardMouse::ButtonsCoords, buttonpressed_),
    PROTOBUF_FIELD_OFFSET(::KeyboardMouse::ButtonsCoords, xcoord_),
    PROTOBUF_FIELD_OFFSET(::KeyboardMouse::ButtonsCoords, ycoord_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    { 0, -1, -1, sizeof(::KeyboardMouse::ButtonsCoords) },
};

static ::PROTOBUF_NAMESPACE_ID::Message const* const file_default_instances[] = {
    reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::KeyboardMouse::_ButtonsCoords_default_instance_),
};

const char descriptor_table_protodef_KeyboardMouseMessage_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = "\n\032KeyboardMouseMessage.proto\022\rKeyboardMo"
                                                                                                                "use\"J\n\rButtonsCoords\022\031\n\rbuttonPressed\030\001 "
                                                                                                                "\003(\010B\002\020\001\022\016\n\006xCoord\030\002 \001(\003\022\016\n\006yCoord\030\003 \001(\003b"
                                                                                                                "\006proto3";
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_KeyboardMouseMessage_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_KeyboardMouseMessage_2eproto = {
    false,
    false,
    127,
    descriptor_table_protodef_KeyboardMouseMessage_2eproto,
    "KeyboardMouseMessage.proto",
    &descriptor_table_KeyboardMouseMessage_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_KeyboardMouseMessage_2eproto::offsets,
    file_level_metadata_KeyboardMouseMessage_2eproto,
    file_level_enum_descriptors_KeyboardMouseMessage_2eproto,
    file_level_service_descriptors_KeyboardMouseMessage_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_KeyboardMouseMessage_2eproto_getter()
{
    return &descriptor_table_KeyboardMouseMessage_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_KeyboardMouseMessage_2eproto(&descriptor_table_KeyboardMouseMessage_2eproto);
namespace KeyboardMouse {

// ===================================================================

class ButtonsCoords::_Internal {
public:
};

ButtonsCoords::ButtonsCoords(::PROTOBUF_NAMESPACE_ID::Arena* arena,
    bool is_message_owned)
    : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned)
    , buttonpressed_(arena)
{
    SharedCtor();
    if (!is_message_owned) {
        RegisterArenaDtor(arena);
    }
    // @@protoc_insertion_point(arena_constructor:KeyboardMouse.ButtonsCoords)
}
ButtonsCoords::ButtonsCoords(const ButtonsCoords& from)
    : ::PROTOBUF_NAMESPACE_ID::Message()
    , buttonpressed_(from.buttonpressed_)
{
    _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
    ::memcpy(&xcoord_, &from.xcoord_,
        static_cast<size_t>(reinterpret_cast<char*>(&ycoord_) - reinterpret_cast<char*>(&xcoord_)) + sizeof(ycoord_));
    // @@protoc_insertion_point(copy_constructor:KeyboardMouse.ButtonsCoords)
}

inline void ButtonsCoords::SharedCtor()
{
    ::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(reinterpret_cast<char*>(&xcoord_) - reinterpret_cast<char*>(this)),
        0, static_cast<size_t>(reinterpret_cast<char*>(&ycoord_) - reinterpret_cast<char*>(&xcoord_)) + sizeof(ycoord_));
}

ButtonsCoords::~ButtonsCoords()
{
    // @@protoc_insertion_point(destructor:KeyboardMouse.ButtonsCoords)
    if (GetArenaForAllocation() != nullptr)
        return;
    SharedDtor();
    _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ButtonsCoords::SharedDtor()
{
    GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ButtonsCoords::ArenaDtor(void* object)
{
    ButtonsCoords* _this = reinterpret_cast<ButtonsCoords*>(object);
    (void)_this;
}
void ButtonsCoords::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*)
{
}
void ButtonsCoords::SetCachedSize(int size) const
{
    _cached_size_.Set(size);
}

void ButtonsCoords::Clear()
{
    // @@protoc_insertion_point(message_clear_start:KeyboardMouse.ButtonsCoords)
    uint32_t cached_has_bits = 0;
    // Prevent compiler warnings about cached_has_bits being unused
    (void)cached_has_bits;

    buttonpressed_.Clear();
    ::memset(&xcoord_, 0, static_cast<size_t>(reinterpret_cast<char*>(&ycoord_) - reinterpret_cast<char*>(&xcoord_)) + sizeof(ycoord_));
    _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ButtonsCoords::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx)
{
#define CHK_(x)                       \
    if (PROTOBUF_PREDICT_FALSE(!(x))) \
    goto failure
    while (!ctx->Done(&ptr)) {
        uint32_t tag;
        ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
        switch (tag >> 3) {
        // repeated bool buttonPressed = 1 [packed = true];
        case 1:
            if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
                ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedBoolParser(_internal_mutable_buttonpressed(), ptr, ctx);
                CHK_(ptr);
            } else if (static_cast<uint8_t>(tag) == 8) {
                _internal_add_buttonpressed(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
                CHK_(ptr);
            } else
                goto handle_unusual;
            continue;
        // int64 xCoord = 2;
        case 2:
            if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
                xcoord_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
                CHK_(ptr);
            } else
                goto handle_unusual;
            continue;
        // int64 yCoord = 3;
        case 3:
            if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
                ycoord_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
                CHK_(ptr);
            } else
                goto handle_unusual;
            continue;
        default:
            goto handle_unusual;
        } // switch
    handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
            CHK_(ptr);
            ctx->SetLastTag(tag);
            goto message_done;
        }
        ptr = UnknownFieldParse(
            tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
    } // while
message_done:
    return ptr;
failure:
    ptr = nullptr;
    goto message_done;
#undef CHK_
}

uint8_t* ButtonsCoords::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const
{
    // @@protoc_insertion_point(serialize_to_array_start:KeyboardMouse.ButtonsCoords)
    uint32_t cached_has_bits = 0;
    (void)cached_has_bits;

    // repeated bool buttonPressed = 1 [packed = true];
    if (this->_internal_buttonpressed_size() > 0) {
        target = stream->WriteFixedPacked(1, _internal_buttonpressed(), target);
    }

    // int64 xCoord = 2;
    if (this->_internal_xcoord() != 0) {
        target = stream->EnsureSpace(target);
        target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(2, this->_internal_xcoord(), target);
    }

    // int64 yCoord = 3;
    if (this->_internal_ycoord() != 0) {
        target = stream->EnsureSpace(target);
        target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(3, this->_internal_ycoord(), target);
    }

    if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
        target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
    }
    // @@protoc_insertion_point(serialize_to_array_end:KeyboardMouse.ButtonsCoords)
    return target;
}

size_t ButtonsCoords::ByteSizeLong() const
{
    // @@protoc_insertion_point(message_byte_size_start:KeyboardMouse.ButtonsCoords)
    size_t total_size = 0;

    uint32_t cached_has_bits = 0;
    // Prevent compiler warnings about cached_has_bits being unused
    (void)cached_has_bits;

    // repeated bool buttonPressed = 1 [packed = true];
    {
        unsigned int count = static_cast<unsigned int>(this->_internal_buttonpressed_size());
        size_t data_size = 1UL * count;
        if (data_size > 0) {
            total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
        }
        total_size += data_size;
    }

    // int64 xCoord = 2;
    if (this->_internal_xcoord() != 0) {
        total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64SizePlusOne(this->_internal_xcoord());
    }

    // int64 yCoord = 3;
    if (this->_internal_ycoord() != 0) {
        total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64SizePlusOne(this->_internal_ycoord());
    }

    return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ButtonsCoords::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ButtonsCoords::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData* ButtonsCoords::GetClassData() const { return &_class_data_; }

void ButtonsCoords::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
    const ::PROTOBUF_NAMESPACE_ID::Message& from)
{
    static_cast<ButtonsCoords*>(to)->MergeFrom(
        static_cast<const ButtonsCoords&>(from));
}

void ButtonsCoords::MergeFrom(const ButtonsCoords& from)
{
    // @@protoc_insertion_point(class_specific_merge_from_start:KeyboardMouse.ButtonsCoords)
    GOOGLE_DCHECK_NE(&from, this);
    uint32_t cached_has_bits = 0;
    (void)cached_has_bits;

    buttonpressed_.MergeFrom(from.buttonpressed_);
    if (from._internal_xcoord() != 0) {
        _internal_set_xcoord(from._internal_xcoord());
    }
    if (from._internal_ycoord() != 0) {
        _internal_set_ycoord(from._internal_ycoord());
    }
    _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ButtonsCoords::CopyFrom(const ButtonsCoords& from)
{
    // @@protoc_insertion_point(class_specific_copy_from_start:KeyboardMouse.ButtonsCoords)
    if (&from == this)
        return;
    Clear();
    MergeFrom(from);
}

bool ButtonsCoords::IsInitialized() const
{
    return true;
}

void ButtonsCoords::InternalSwap(ButtonsCoords* other)
{
    using std::swap;
    _internal_metadata_.InternalSwap(&other->_internal_metadata_);
    buttonpressed_.InternalSwap(&other->buttonpressed_);
    ::PROTOBUF_NAMESPACE_ID::internal::memswap<
        PROTOBUF_FIELD_OFFSET(ButtonsCoords, ycoord_)
        + sizeof(ButtonsCoords::ycoord_)
        - PROTOBUF_FIELD_OFFSET(ButtonsCoords, xcoord_)>(
        reinterpret_cast<char*>(&xcoord_),
        reinterpret_cast<char*>(&other->xcoord_));
}

::PROTOBUF_NAMESPACE_ID::Metadata ButtonsCoords::GetMetadata() const
{
    return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
        &descriptor_table_KeyboardMouseMessage_2eproto_getter, &descriptor_table_KeyboardMouseMessage_2eproto_once,
        file_level_metadata_KeyboardMouseMessage_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
} // namespace KeyboardMouse
PROTOBUF_NAMESPACE_OPEN
template <>
PROTOBUF_NOINLINE ::KeyboardMouse::ButtonsCoords* Arena::CreateMaybeMessage<::KeyboardMouse::ButtonsCoords>(Arena* arena)
{
    return Arena::CreateMessageInternal<::KeyboardMouse::ButtonsCoords>(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
