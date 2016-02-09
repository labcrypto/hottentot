/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 10-02-2016 03:06:23
 * Name: date_time.h
 * Description:
 *   This file contains definition of DateTime class.
 ***************************************************************/

#ifndef _EXAMPLE_GENERATED_ABC_XYZ__DATE_TIME_H_
#define _EXAMPLE_GENERATED_ABC_XYZ__DATE_TIME_H_

#include <string>

#include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/serializable.h>


namespace example {
namespace generated {
namespace abc {
namespace xyz {
  class DateTime : public ::naeem::hottentot::runtime::Serializable {
  public:
    DateTime() {}
    DateTime(const DateTime &);
    DateTime(DateTime *);
    virtual ~DateTime() {}
  public:
    inline ::naeem::hottentot::runtime::types::UInt8 GetYear() const {
      return year_;
    }
    inline void SetYear(::naeem::hottentot::runtime::types::UInt8 year) {
      year_ = year;
    }
    inline ::naeem::hottentot::runtime::types::UInt8 GetMonth() const {
      return month_;
    }
    inline void SetMonth(::naeem::hottentot::runtime::types::UInt8 month) {
      month_ = month;
    }
    inline ::naeem::hottentot::runtime::types::UInt8 GetDay() const {
      return day_;
    }
    inline void SetDay(::naeem::hottentot::runtime::types::UInt8 day) {
      day_ = day;
    }
  public:
    virtual unsigned char * Serialize(uint32_t * /* Pointer to length */);
    virtual void Deserialize(unsigned char * /* Data */, uint32_t /* Data length */);
  private:
    ::naeem::hottentot::runtime::types::UInt8 year_;
    ::naeem::hottentot::runtime::types::UInt8 month_;
    ::naeem::hottentot::runtime::types::UInt8 day_;
  };
} // END OF NAMESPACE xyz
} // END OF NAMESPACE abc
} // END OF NAMESPACE generated
} // END OF NAMESPACE example

#endif