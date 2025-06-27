#include <libcategory/category.hpp>

namespace Category
{
inline std::unordered_map<std::string, Name> extension_to_category = {
	// Audio
	{ "mp3", Name::audio },
	{ "wav", Name::audio },
	{ "flac", Name::audio },
	{ "aac", Name::audio },
	{ "ogg", Name::audio },
	{ "m4a", Name::audio },

	// Video
	{ "mp4", Name::video },
	{ "mkv", Name::video },
	{ "mov", Name::video },
	{ "avi", Name::video },
	{ "webm", Name::video },
	{ "flv", Name::video },

	// Photos / Images
	{ "jpg", Name::photo },
	{ "jpeg", Name::photo },
	{ "png", Name::photo },
	{ "gif", Name::photo },
	{ "bmp", Name::photo },
	{ "webp", Name::photo },
	{ "tiff", Name::photo },
	{ "svg", Name::photo },

	// Documents
	{ "txt", Name::document },
	{ "md", Name::document },
	{ "doc", Name::document },
	{ "docx", Name::document },
	{ "pdf", Name::document },
	{ "odt", Name::document },
	{ "rtf", Name::document },
	{ "tex", Name::document },

	// Presentations
	{ "ppt", Name::presentation },
	{ "pptx", Name::presentation },
	{ "odp", Name::presentation },
	{ "key", Name::presentation },

	// Archives / Compressed
	{ "zip", Name::zip },
	{ "gz", Name::zip },
	{ "tar", Name::zip },
	{ "rar", Name::zip },
	{ "7z", Name::zip },
	{ "xz", Name::zip },
	{ "bz2", Name::zip },
	{ "iso", Name::zip }
};

inline std::unordered_map<Name, std::string> category_to_directory = {
	{ Name::audio, "audios" }, { Name::document, "documents" },
	{ Name::photo, "photos" }, { Name::presentation, "presentations" },
	{ Name::video, "videos" }, { Name::zip, "zips" },
};
} // namespace Category
