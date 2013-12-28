import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    id: root_item

    property Item current_page
    property Item next_page

    property alias word_page: words_page_item
    clip:true

    Home_page {
        id: home_page_item
    }

    Words_page {
        id: words_page_item
    }

    Thema_page {
        id: thema_page_item
    }

    Result_page {
        id: result_page_item
    }

    Help_page {
        id: help_page_item
    }

    Stats_page {
        id: stats_page_item
    }

    About_page {
       id: about_page_item
    }

}
