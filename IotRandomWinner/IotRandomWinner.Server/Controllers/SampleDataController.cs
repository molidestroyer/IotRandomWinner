using IotRandomWinner.Server.iot;
using IotRandomWinner.Shared;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace IotRandomWinner.Server.Controllers
{
    [Route("api/[controller]")]
    public class SampleDataController : Controller
    {
        public int MAX_COUNT_OF_DEVICES = 100;
        public string CONNECTION_STRING = "HostName=ERNI-IOT-EDGE-HUB.azure-devices.net;SharedAccessKeyName=mxchipgif;SharedAccessKey=5HDv1uo1F4UinBnBaF/Y9GJ0R+mzLT1CWXakfDYOrcA=";
        private readonly DevicesProcessor devicesProcessor;

        public SampleDataController()
        {
            this.devicesProcessor = new DevicesProcessor(CONNECTION_STRING, MAX_COUNT_OF_DEVICES, string.Empty);
        }

        [HttpGet("[action]")]
        public IEnumerable<DeviceEntity> WeatherForecasts()
        {
            var rng = new Random();
            var devices = this.devicesProcessor.GetDevices().Result;
            return devices;
        }

        [HttpPost("[action]")]
        public async Task InvokeDeviceMethodAsync([FromBody] RandomItemRequest method)
        {
            var rng = new Random();
            await this.devicesProcessor.InvokeDeviceMethodAsync(method.DeviceId.FirstOrDefault(), method.Method);
            
        }
    }
}
