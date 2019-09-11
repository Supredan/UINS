// Auto-generated. Do not edit!

// (in-package bitcraze_lps_estimator.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RangeArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ranges = null;
      this.valid = null;
      this.los = null;
    }
    else {
      if (initObj.hasOwnProperty('ranges')) {
        this.ranges = initObj.ranges
      }
      else {
        this.ranges = [];
      }
      if (initObj.hasOwnProperty('valid')) {
        this.valid = initObj.valid
      }
      else {
        this.valid = [];
      }
      if (initObj.hasOwnProperty('los')) {
        this.los = initObj.los
      }
      else {
        this.los = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RangeArray
    // Serialize message field [ranges]
    bufferOffset = _arraySerializer.float32(obj.ranges, buffer, bufferOffset, null);
    // Serialize message field [valid]
    bufferOffset = _arraySerializer.bool(obj.valid, buffer, bufferOffset, null);
    // Serialize message field [los]
    bufferOffset = _arraySerializer.bool(obj.los, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RangeArray
    let len;
    let data = new RangeArray(null);
    // Deserialize message field [ranges]
    data.ranges = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [valid]
    data.valid = _arrayDeserializer.bool(buffer, bufferOffset, null)
    // Deserialize message field [los]
    data.los = _arrayDeserializer.bool(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.ranges.length;
    length += object.valid.length;
    length += object.los.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'bitcraze_lps_estimator/RangeArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6eea5c2b2055cd08369bcbebe9f0032b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[] ranges
    bool[] valid
    bool[] los
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RangeArray(null);
    if (msg.ranges !== undefined) {
      resolved.ranges = msg.ranges;
    }
    else {
      resolved.ranges = []
    }

    if (msg.valid !== undefined) {
      resolved.valid = msg.valid;
    }
    else {
      resolved.valid = []
    }

    if (msg.los !== undefined) {
      resolved.los = msg.los;
    }
    else {
      resolved.los = []
    }

    return resolved;
    }
};

module.exports = RangeArray;
