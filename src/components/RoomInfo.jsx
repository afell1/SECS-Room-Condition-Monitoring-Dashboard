export default function ViewReadingItem({room, tempF, rhPercent, timestamp}) {
    return (
        <div>
            <table className="table-item">
                <tr>
                    <td style={{width: "30%"}}>{timestamp}</td>
                    <td style={{width: "20%"}}>{room}</td>
                    <td style={{width: "25%"}}>{tempF.toFixed(2)}</td>
                    <td style={{width: "25%"}}>{rhPercent.toFixed(2)}</td>
                </tr>
            </table>
        </div>
    )
}