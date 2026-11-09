import "./App.css";
import ViewReadingItem from "./components/RoomInfo.jsx";
import { readings, rooms } from "./data.js";
import { useState } from "react";
import { Line } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
} from "chart.js";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

export default function Dashboard() {
  const [view, setView] = useState('SHOW ALL');
  const switchView = (event) => {
    setView(event.target.value);
  }

  const filteredReadings = 
    view === 'SHOW ALL' ? readings : readings.filter((reading =>
      reading.room === view
    ))

  const data = filteredReadings.map(reading =>
    <ViewReadingItem
        key={reading.id}
        room={reading.room}
        tempF={reading.tempF}
        rhPercent={reading.rhPercent}
        timestamp={reading.timestamp}
    />
  )

  return (
    <div>
      <h2>SECS Room Condition Monitoring Dashboard</h2>

      <section className="room-view">
        <form>
          <p>Select a room to view readings:</p>
          <select value={view} onChange={switchView}>
            {rooms.map(room => (
              <option key={room.id} value={room.room}>
                {room.room}
              </option>
            ))}
          </select>
        </form>
      </section>
      <div className="main">
        <section className="charts"> 
          <Line 
            data={{
              labels: filteredReadings.map(reading => reading.timestamp),
              datasets: [
                {
                  label: 'Temperature (°F)',
                  data: filteredReadings.map(reading => reading.tempF)
                },
              ]
            }}
          />
          <Line 
            data={{
              labels: filteredReadings.map(reading => reading.timestamp),
              datasets: [
                {
                  label: 'Humidity (%)',
                  data: filteredReadings.map(reading => reading.rhPercent)
                },
              ]
            }}
          />
        </section>

        <section className="readings-table">
          <table className="table-header">
              <tr>
                  <td style={{border: "none", width: "30%"}}>Timestamp</td>
                  <td style={{border: "none", width: "20%"}}>Location</td>
                  <td style={{border: "none", width: "25%"}}>Temperature (F)</td>
                  <td style={{border: "none", width: "25%"}}>Humidity (%)</td>
              </tr>
          </table>

          {data.toReversed()}
        </section>
      </div>
    </div>
  )
}