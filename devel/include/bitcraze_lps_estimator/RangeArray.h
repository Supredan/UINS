// Generated by gencpp from file bitcraze_lps_estimator/RangeArray.msg
// DO NOT EDIT!


#ifndef BITCRAZE_LPS_ESTIMATOR_MESSAGE_RANGEARRAY_H
#define BITCRAZE_LPS_ESTIMATOR_MESSAGE_RANGEARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace bitcraze_lps_estimator
{
template <class ContainerAllocator>
struct RangeArray_
{
  typedef RangeArray_<ContainerAllocator> Type;

  RangeArray_()
    : ranges()
    , valid()
    , los()  {
    }
  RangeArray_(const ContainerAllocator& _alloc)
    : ranges(_alloc)
    , valid(_alloc)
    , los(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _ranges_type;
  _ranges_type ranges;

   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _valid_type;
  _valid_type valid;

   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _los_type;
  _los_type los;





  typedef boost::shared_ptr< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> const> ConstPtr;

}; // struct RangeArray_

typedef ::bitcraze_lps_estimator::RangeArray_<std::allocator<void> > RangeArray;

typedef boost::shared_ptr< ::bitcraze_lps_estimator::RangeArray > RangeArrayPtr;
typedef boost::shared_ptr< ::bitcraze_lps_estimator::RangeArray const> RangeArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace bitcraze_lps_estimator

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'bitcraze_lps_estimator': ['/home/supdan/code/UINS_ws/src/lps-ros/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6eea5c2b2055cd08369bcbebe9f0032b";
  }

  static const char* value(const ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6eea5c2b2055cd08ULL;
  static const uint64_t static_value2 = 0x369bcbebe9f0032bULL;
};

template<class ContainerAllocator>
struct DataType< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bitcraze_lps_estimator/RangeArray";
  }

  static const char* value(const ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32[] ranges\n\
bool[] valid\n\
bool[] los\n\
";
  }

  static const char* value(const ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ranges);
      stream.next(m.valid);
      stream.next(m.los);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RangeArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::bitcraze_lps_estimator::RangeArray_<ContainerAllocator>& v)
  {
    s << indent << "ranges[]" << std::endl;
    for (size_t i = 0; i < v.ranges.size(); ++i)
    {
      s << indent << "  ranges[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.ranges[i]);
    }
    s << indent << "valid[]" << std::endl;
    for (size_t i = 0; i < v.valid.size(); ++i)
    {
      s << indent << "  valid[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.valid[i]);
    }
    s << indent << "los[]" << std::endl;
    for (size_t i = 0; i < v.los.size(); ++i)
    {
      s << indent << "  los[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.los[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // BITCRAZE_LPS_ESTIMATOR_MESSAGE_RANGEARRAY_H