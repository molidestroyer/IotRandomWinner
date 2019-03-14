using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
namespace IotRandomWinner.Shared
{
    public class RandomItemRequest
    {
        public string Method { get; set; }
        public List<DeviceEntity> DeviceId { get; set; }

    }
}
