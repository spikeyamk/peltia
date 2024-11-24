#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>

#include "sens/max31865/rtd.hpp"
#include "to_json.hpp"

#include "charts.hpp"

namespace admin {
    Charts::Charts(QWidget* parent) :
        QWidget { parent },
        layout { new QVBoxLayout(this) },
        scroll_content { new QWidget(this) },
        scroll_content_layout { new QVBoxLayout(scroll_content) },
        scroll_area { new QScrollArea(this) },
        json_array { new QJsonArray() }
    {
        scroll_content->setLayout(scroll_content_layout);
        scroll_area->setWidget(scroll_content);
        scroll_area->setWidgetResizable(true);

        layout->addWidget(scroll_area);

        setup_chart(
            max31865_front_series,
            max31865_rear_series,
            max31865_chart,
            max31865_chart_view,
            "front",
            "rear",
            "MAX31865",
            "Time [s]",
            "Temperature [°C]"
        );

        setup_chart(
            dmax31865_front_series,
            dmax31865_rear_series,
            dmax31865_chart,
            dmax31865_chart_view,
            "front",
            "rear",
            "dMAX31865",
            "Time [s]",
            "dTemperature [°C/s]"
        );

        setup_chart(
            dac_front_series,
            dac_rear_series,
            dac_chart,
            dac_chart_view,
            "front",
            "rear",
            "DAC",
            "Time [s]",
            "DAC Code (12-bit)"
        );

        setup_chart(
            p_front_series,
            p_rear_series,
            p_chart,
            p_chart_view,
            "front",
            "rear",
            "P",
            "Time [s]",
            "Value"
        );

        setup_chart(
            i_front_series,
            i_rear_series,
            i_chart,
            i_chart_view,
            "front",
            "rear",
            "I",
            "Time [s]",
            "Value"
        );

        setup_chart(
            d_front_series,
            d_rear_series,
            d_chart,
            d_chart_view,
            "front",
            "rear",
            "D",
            "Time [s]",
            "Value"
        );

        setup_chart(
            sht31_front_series,
            sht31_rear_series,
            sht31_chart,
            sht31_chart_view,
            "inside",
            "outside",
            "SHT31",
            "Time [s]",
            "Temperature [°C]"
        );
    }

    Charts::~Charts() {
        delete json_array;
    }

    void Charts::setup_chart(
        QLineSeries*& first_series,
        QLineSeries*& second_series,
        QChart*& chart,
        QChartView*& chart_view,
        const QString& first_series_name,
        const QString& second_series_name,
        const QString& chart_title,
        const QString& x_axis_text,
        const QString& y_axis_text
    ) {
        const QPen first_pen(QBrush(QColor("orange")), 2.0);
        const QPen second_pen(QBrush(QColorConstants::Green), 2.0);

        first_series = new QLineSeries(this);
        second_series = new QLineSeries(this);
        chart = new QChart();
        chart_view = new QChartView(chart, this);

        first_series->setName(first_series_name);
        first_series->setPen(first_pen);

        second_series->setName(second_series_name);
        second_series->setPen(second_pen);

        chart->addSeries(first_series);
        chart->addSeries(second_series);

        chart->createDefaultAxes();
        chart->setTitle(chart_title);
        chart->axes(Qt::Vertical).front()->setTitleText(y_axis_text);
        chart->axes(Qt::Horizontal).front()->setTitleText(x_axis_text);

        chart_view->setRenderHint(QPainter::Antialiasing);

        scroll_content_layout->addWidget(chart_view);
        chart_view->setMinimumSize(
            QApplication::primaryScreen()->geometry().width() - (QApplication::primaryScreen()->geometry().width() / 12),
            (QApplication::primaryScreen()->geometry().height() / 2) - (QApplication::primaryScreen()->geometry().height() / 12)
        );
    }

    void Charts::autoscale_axes(QChart* chart, QLineSeries* first_series, QLineSeries* second_series) {
        qreal max_x = -std::numeric_limits<qreal>::infinity();
        qreal min_x = std::numeric_limits<qreal>::infinity();
        qreal max_y = -std::numeric_limits<qreal>::infinity();
        qreal min_y = std::numeric_limits<qreal>::infinity();

        for(const auto& point : first_series->points()) {
            if(point.x() > max_x) {
                max_x = point.x();
            }
            if(point.x() < min_x) {
                min_x = point.x();
            }
        }

        for(const auto& point : second_series->points()) {
            if(point.x() > max_x) {
                max_x = point.x();
            }
            if(point.x() < min_x) {
                min_x = point.x();
            }
        }

        for(const auto& point : first_series->points()) {
            if(point.y() > max_y) {
                max_y = point.y();
            }
            if(point.y() < min_y) {
                min_y = point.y();
            }
        }
        
        for(const auto& point : second_series->points()) {
            if(point.y() > max_y) {
                max_y = point.y();
            }
            if(point.y() < min_y) {
                min_y = point.y();
            }
        }

        chart->axes(Qt::Horizontal).first()->setMax(max_x);
        chart->axes(Qt::Horizontal).first()->setMin(min_x);
        chart->axes(Qt::Vertical).first()->setMax(max_y);
        chart->axes(Qt::Vertical).first()->setMin(min_y);
    }

    void Charts::push_to_chart(
        QLineSeries* first_series,
        QLineSeries* second_series,
        QChart* chart,
        const qreal x_value,
        const qreal first_y_value,
        const qreal second_y_value
    ) {
        first_series->append(x_value, first_y_value);
        second_series->append(x_value, second_y_value);
        autoscale_axes(chart, first_series, second_series);
    }

    void Charts::push_to_charts(const magic::results::ReadTempCtl sample) {
        static const qreal msecs_since_epoch { static_cast<qreal>(QDateTime::currentMSecsSinceEpoch()) };
        const qreal x_value {
            (static_cast<qreal>(QDateTime::currentMSecsSinceEpoch()) - msecs_since_epoch)
            / 1000.0f 
        };

        const qreal max31865_front {
            sens::max31865::RTD(sens::max31865::ADC_Code(sample.max31865_front).serialize())
                .calculate_approx_temp().value()
        };
        const qreal max31865_rear {
            sens::max31865::RTD(sens::max31865::ADC_Code(sample.max31865_rear).serialize())
                .calculate_approx_temp().value()
        };
        push_to_chart(
            max31865_front_series,
            max31865_rear_series,
            max31865_chart,
            x_value,
            max31865_front,
            max31865_rear
        );

        push_to_chart(
            p_front_series,
            p_rear_series,
            p_chart,
            x_value,
            sample.p_front,
            sample.p_rear
        );

        push_to_chart(
            i_front_series,
            i_rear_series,
            i_chart,
            x_value,
            sample.i_front,
            sample.i_rear
        );

        push_to_chart(
            d_front_series,
            d_rear_series,
            d_chart,
            x_value,
            sample.d_front,
            sample.d_rear
        );

        static qreal max31865_front_before { max31865_front };
        static qreal max31865_rear_before { max31865_rear };
        push_to_chart(
            dmax31865_front_series,
            dmax31865_rear_series,
            dmax31865_chart,
            x_value,
            max31865_front_before - max31865_front,
            max31865_rear_before - max31865_rear
        );
        max31865_front_before = max31865_front;
        max31865_rear_before = max31865_rear;

        push_to_chart(
            dac_front_series,
            dac_rear_series,
            dac_chart,
            x_value,
            static_cast<qreal>(sample.dac_front),
            static_cast<qreal>(sample.dac_rear)
        );

        json_array->append(to_json(sample)["time"] = x_value);
    }

    void Charts::dump_to_file(const QString& file_path) {
        QFile file(file_path);
        if(file.open(QIODevice::WriteOnly) == false) {
            const auto error { file.error() };
            const QString tmp_message {
                QString(typeid(error).name())
                + ": &QFile::write: "
                + QVariant::fromValue(error).toString()
            };

            emit log(QString(typeid(*this).name()) + ": " + tmp_message);
        }

        const auto write_buf { QJsonDocument(*json_array).toJson(QJsonDocument::Indented) };
        if(file.write(write_buf) != write_buf.size()) {
            const auto error { file.error() };
            const QString tmp_message {
                QString(typeid(error).name())
                + ": &QFile::write: "
                + QVariant::fromValue(error).toString()
            };

            emit log(QString(typeid(*this).name()) + ": " + tmp_message);
        }
    }
}