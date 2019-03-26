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
        public IEnumerable<DeviceEntity> GetDevices()
        {
            var rng = new Random();
            var devices = this.devicesProcessor.GetDevices().Result;
            return devices;
        }

        [HttpGet("[action]")]
        public IEnumerable<WorkshopList> GetWorkshops()
        {
            var workshops = new List<WorkshopList>();
            workshops.Add(new WorkshopList() {
                Name= "iot the beginning",
                Assitants = new List<string> { "Oscar vaquero viñes", "Miguel Molina", "Robert Cluet", "Manolete garcia perez", "David bustamante" }
            }            );
            workshops.Add(new WorkshopList()
            {
                Name = "iot 2 the return",
                Assitants = new List<string> { "Oscar vaquero viñes2", "Miguel Molina2", "Robert Cluet2", "Manolete garcia perez2", "David bustamante2" }
            });
            workshops.Add(new WorkshopList()
            {
                Name = "iot 3 the dummy",
                Assitants = new List<string> { "Oscar vaquero viñes3", "Miguel Molina3", "Robert Cluet3", "Manolete garcia perez3", "David bustamante3" }
            });
            return workshops;
        }

        [HttpPost("[action]")]
        public async Task InvokeDeviceMethodAsync([FromBody] RandomItemRequest method)
        {
            foreach (var device in method.Devices)
            {
                var rng = new Random();
                int index = rng.Next(method.Assistants.Count);
                await this.devicesProcessor.InvokeDeviceMethodAsync(device, method.Method, new Payload { Name = method.Assistants[index] });
            }
            
        }
    }
}
